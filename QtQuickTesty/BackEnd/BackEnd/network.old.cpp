#include "network.h"

Network::Network(QObject* parent)
{
	// connect to api events
	QObject::connect(&server, &QTcpServer::newConnection, this, &Network::NewConnection);
	QObject::connect(&socket, &QIODevice::readyRead, this, &Network::ReadyRead);
	QObject::connect(&socket, &QTcpSocket::errorOccurred, this, &Network::ConnectionError);
	QObject::connect(&socket, &QTcpSocket::connected, this, &Network::Connected);
}

std::string Network::GenerateLobbyCode()
{
	//QHostAddress& addr = QHostAddress(QHostAddress::AnyIPv4);
	const QHostAddress& localhost = QHostAddress(QHostAddress::LocalHost);
	for (const QHostAddress& address : QNetworkInterface::allAddresses())
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
			return address.toString().toStdString();
	}
}

void Network::StartServer()
{
	onLog("Attempting Serverlaunch");
	if (server.isListening())
	{
		onLog("Listening on Port: " + std::to_string(server.serverPort()));
		server.close();
		qDebug() << server.listen(QHostAddress::Any, PORT);	//error msg or exception can be thrown here
		onLog("Listening on Port: " + std::to_string(server.serverPort()));
	}
	else
	{
		onLog("Listening " + std::to_string(server.listen(QHostAddress::Any, PORT)));	//error msg or exception can be thrown here
		onLog("Port: " + std::to_string(server.serverPort()));
	}
}

void Network::ConnectToServer(const std::string& ip)
{
	QHostAddress addr;
	addr.setAddress(QString(ip.c_str()));
	socket.connectToHost(addr, PORT); 
}

Network::~Network()
{
	server.close();
	socket.close();
	for (auto& cn : connections)
		cn->close();
}

void Network::NewConnection()
{
	auto connection = server.nextPendingConnection();
	connections.push_back(connection);
	onLog("A Client has Connected"); //trigger event
}

void Network::ReadyRead()
{
	//read
	//render data
	onDataReceived("Some Data was Received by Client");
}

void Network::ConnectionError(QAbstractSocket::SocketError)
{
	onLog("Could not connect to Server");
}

void Network::Connected()
{
	onLog("Connected To Server");
}
