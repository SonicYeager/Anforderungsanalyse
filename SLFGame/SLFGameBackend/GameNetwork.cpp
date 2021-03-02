#include "GameNetwork.h"

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
	m_socket.connectToHost(address, m_port);
}

void GameNetwork::Write(const QByteArray& data, int idx)
{
	m_connections[idx]->write(data, sizeof(NetworkData));
}

void GameNetwork::Broadcast(const QByteArray& data)
{
	for (size_t i{}; i < m_connections.size(); ++i)
		Write(data, i);
}

void GameNetwork::WriteToHost(const QByteArray& data)
{
	if (m_connections.size() == 0)
		m_socket.write(data, sizeof(NetworkData));
	else
		m_connections[0]->write(data, sizeof(NetworkData));
}

void GameNetwork::ReadyRead()
{
	QByteArray qdata{};
	qdata = m_socket.read(sizeof(NetworkData));
	onReadyRead(qdata);
}

void GameNetwork::NewConnection()
{
	auto newConnection = m_server.nextPendingConnection();
	m_connections.push_back(newConnection);
	onNewConnection(m_connections.size() - 1);
}
