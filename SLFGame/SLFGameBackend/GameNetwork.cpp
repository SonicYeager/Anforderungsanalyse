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

void GameNetwork::ReadyRead()
{
	//reader
}

void GameNetwork::NewConnection()
{
	m_connections.push_back(m_server.nextPendingConnection());
	onNewConnection();
}
