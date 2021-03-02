#include "GameNetwork.h"

const int readlength = sizeof(NetworkData);

GameNetwork::GameNetwork(QObject* parent)
{
	QObject::connect(&m_server, &QTcpServer::newConnection, this, &GameNetwork::NewConnection);
	QObject::connect(&m_socket, &QIODevice::readyRead, this, &GameNetwork::ReadyRead);
}

GameNetwork::~GameNetwork()
{
	m_socket.close();
	for (auto& connection : m_connections)
		connection->close();
	m_server.close();
}

std::string GameNetwork::GenerateLobbyCode()
{

	const QHostAddress&	localhost	= QHostAddress(QHostAddress::LocalHost);

	for (const QHostAddress& address : QNetworkInterface::allAddresses()) 
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
		{
			m_serverAddress = address;
			return address.toString().toStdString();
		}
	}
}

void GameNetwork::StartServer()
{
	if (m_server.isListening())
	{
		m_server.close();
		m_server.listen(m_serverAddress, m_port);
	}
	else
	{
		m_server.listen(m_serverAddress, m_port);
	}
}

void GameNetwork::ConnectToServer(const std::string& ip)
{
	QHostAddress address;
	address.setAddress(QString(ip.c_str()));
	m_socket.connectToHost(address, m_port, QIODeviceBase::ReadWrite);
}

void GameNetwork::Write(const QByteArray& data, int idx)
{
	int written = m_connections[idx]->write(data, sizeof(NetworkData));
	if (written == -1) throw;
}

void GameNetwork::Broadcast(const QByteArray& data)
{
	for (size_t i{}; i < m_connections.size(); ++i)
		Write(data, i);
}

void GameNetwork::WriteToHost(const QByteArray& data)
{
	int written = 0;
	if (m_connections.size() == 0)
	{
		written = m_socket.write(data, sizeof(NetworkData));
	}
	else
	{
		written = m_connections[0]->write(data, sizeof(NetworkData));
	}
	if (written == -1) throw;
	if (written < 216) throw;
}

void GameNetwork::ReadyRead()
{
	QByteArray qdata{};
	if(m_socket.bytesAvailable() == sizeof(NetworkData))
		qdata = m_socket.read(sizeof(NetworkData));
	for (size_t i{}; i < m_connections.size(); ++i)
		if (m_connections[i]->bytesAvailable() == sizeof(NetworkData))
			qdata = m_connections[i]->read(sizeof(NetworkData));
	onReadyRead(qdata);
}

void GameNetwork::NewConnection()
{
	auto newConnection = m_server.nextPendingConnection();
	m_connections.push_back(newConnection);
	QObject::connect(newConnection, &QIODevice::readyRead, this, &GameNetwork::ReadyRead);
	onNewConnection(m_connections.size() - 1);
}
