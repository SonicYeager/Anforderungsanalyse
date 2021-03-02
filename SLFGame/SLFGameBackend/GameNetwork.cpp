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

void GameNetwork::Write(const QDataStream& data, int idx)
{
	m_connections[idx]->write((char*)&data, sizeof(NetworkData));
}

void GameNetwork::Broadcast(const QDataStream& data)
{
	for (size_t i{}; i < m_connections.size(); ++i)
		Write(data, i);
}

void GameNetwork::WriteToHost(const QDataStream& data)
{
	m_socket.write((char*)&data, sizeof(NetworkData));
}

void GameNetwork::ReadyRead()
{
	NetworkData	ndata;
	QByteArray qdata{};
	m_socket.read((char*)&ndata, sizeof(NetworkData));
	onReadyRead(ndata);
}

void GameNetwork::NewConnection()
{
	auto newConnection = m_server.nextPendingConnection();
	m_connections.push_back(newConnection);
	//get other playernames
	NetworkData ndata;
	ndata.header = HEADER::GET;
	ndata.potentialId = 333;//m_connections.size() - 1;
	newConnection->write((char*)&ndata, sizeof(NetworkData));
	//***********************
	onNewConnection(m_connections.size() - 1);
}
