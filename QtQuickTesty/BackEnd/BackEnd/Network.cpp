#pragma once
#include "Network.h"
#include <fstream>

Network::Network()
{
	QObject::connect(&m_server, &QTcpServer::newConnection,				this, &Network::OnNewConnection);
	QObject::connect(&m_server, &QTcpServer::acceptError,				this, &Network::OnHostConnectError);

	QObject::connect(&m_serverSocket, &QTcpSocket::connected,			this, &Network::OnSelfConnected);
	QObject::connect(&m_serverSocket, &QAbstractSocket::disconnected,	this, &Network::OnSelfDisconnect);
	QObject::connect(&m_serverSocket, &QIODevice::readyRead,			this, &Network::OnSelfReceivedData);
	QObject::connect(&m_serverSocket, &QTcpSocket::errorOccurred,		this, &Network::OnSelfClientConnectError);
	QObject::connect(&m_serverSocket, &QTcpSocket::bytesWritten,		this, &Network::OnSelfBytesWritten);
	QObject::connect(&m_serverSocket, &QTcpSocket::hostFound,			this, &Network::OnSelfHostFound);
	QObject::connect(&m_serverSocket, &QTcpSocket::stateChanged,		this, &Network::OnSelfStateChanged);
}

std::string Network::GenerateLobbyCode()
{
	const QHostAddress& localhost = QHostAddress(QHostAddress::LocalHost);
	for (const QHostAddress& address : QNetworkInterface::allAddresses()) 
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
			return address.toString().toStdString();
	}
	return localhost.toString().toStdString();
}

LobbyCode Network::StartServer()
{
	m_server.moveToThread(&serverThread);
	serverThread.start();

	auto checker = m_server.listen(QHostAddress::Any, PORT);
	std::string b = checker == true ? "True" : "False";
	onLog("Server Listen: " + b);
	auto lobbyCode = GenerateLobbyCode();
	return lobbyCode;
}

void Network::ConnectToServer(const LobbyCode& code) 
{
	m_serverSocket.connectToHost(QHostAddress(code.c_str()), PORT, QIODeviceBase::ReadWrite);
	onLog("Attempting to connect to Host...");
}

void Network::WriteTo(const ByteStream& data, int id)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	sizestream << sizeof(data);
	sizestream.writeBytes(data.data(), data.size());
	m_sockets[id]->write(qdata);
	onLog("Data has been send to client: " + std::to_string(id));
}

void Network::WriteToHost(const ByteStream& data)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	sizestream << sizeof(data);
	sizestream.writeBytes(data.data(), data.size());
	m_serverSocket.write(qdata);
	onLog("Data has been send to Host!");
}

void Network::Broadcast(const ByteStream& data)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	sizestream << sizeof(data);
	sizestream.writeBytes(data.data(), data.size());
	for (const auto& socket : m_sockets)
		socket->write(qdata);
	onLog("Data has been Broadcasted!");
}

ByteStream Network::WaitForData()
{
	m_serverSocket.waitForReadyRead(2000);
	auto qreadsize = m_serverSocket.read(HEADERSIZE);
	QDataStream sizestream{ qreadsize };
	int size{};
	sizestream >> size;
	auto qdata = m_serverSocket.read(size);
	std::vector<char> data{ std::begin(qdata), std::end(qdata) };
	onLog("Data has been Received!");
	return data;
}

ByteStream Network::WaitForData(int id)
{
	m_sockets[id]->waitForReadyRead(2000);
	auto qreadsize = m_sockets[id]->read(HEADERSIZE);
	QDataStream sizestream{ qreadsize };
	int size{};
	sizestream >> size;
	auto qdata = m_sockets[id]->read(size);
	std::vector<char> data{ std::begin(qdata), std::end(qdata) };
	onLog("Data has been Received on Client: " + std::to_string(id));
	return data;
}

void Network::WaitForNewConnection()
{
	m_server.waitForNewConnection(2000);
	auto conn = m_server.nextPendingConnection();
	m_sockets.push_back(std::unique_ptr<QTcpSocket>(conn));
	auto id = m_sockets.size() - 1;

	QObject::connect(&*m_sockets[id], &QTcpSocket::connected,		[this, id]()											{OnClientConnected(id);});
	QObject::connect(&*m_sockets[id], &QTcpSocket::disconnected,	[this, id]()											{OnClientDisconnect(id);});
	QObject::connect(&*m_sockets[id], &QIODevice::readyRead,		[this, id]()											{OnClientReceivedData(id);});
	QObject::connect(&*m_sockets[id], &QTcpSocket::errorOccurred,	[this, id](const QAbstractSocket::SocketError& err)		{OnClientClientConnectError(err, id);});
	QObject::connect(&*m_sockets[id], &QTcpSocket::bytesWritten,	[this, id](int written)									{OnClientBytesWritten(written, id);});
	QObject::connect(&*m_sockets[id], &QTcpSocket::hostFound,		[this, id]()											{OnClientHostFound(id);});
	QObject::connect(&*m_sockets[id], &QTcpSocket::stateChanged,	[this, id](const QAbstractSocket::SocketState& state)	{OnClientStateChanged(state, id);});

	onLog("New Connection of Client: " + std::to_string(id));
}

void Network::WaitForConnection()
{
	m_serverSocket.waitForConnected(2000);
	onLog("Client Connected to Host");
}

void Network::OnNewConnection()
{
	auto conn = m_server.nextPendingConnection();
	m_sockets.emplace_back(conn);
	auto id = m_sockets.size()-1;

	QObject::connect(&*m_sockets[id], &QTcpSocket::connected,		[this, id]()											{OnClientConnected(id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::disconnected,	[this, id]()											{OnClientDisconnect(id); });
	QObject::connect(&*m_sockets[id], &QIODevice::readyRead,		[this, id]()											{OnClientReceivedData(id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::errorOccurred,	[this, id](const QAbstractSocket::SocketError& err)		{OnClientClientConnectError(err, id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::bytesWritten,	[this, id](int written)									{OnClientBytesWritten(written, id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::hostFound,		[this, id]()											{OnClientHostFound(id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::stateChanged,	[this, id](const QAbstractSocket::SocketState& state)	{OnClientStateChanged(state, id); });

	onLog("New Connection of Client: " + std::to_string(id));
}

void Network::OnSelfReceivedData()
{
	if (m_serverSocket.bytesAvailable() > 0)
	{
		auto qreadsize = m_serverSocket.read(HEADERSIZE);
		QDataStream sizestream{ qreadsize };
		int size{};
		sizestream >> size;
		auto qdata = m_serverSocket.read(size);
		std::vector<char> data{ std::begin(qdata), std::end(qdata) };
		onLog("Data Received!");
		onData(data);
	}
}

void Network::OnClientClientConnectError(const QAbstractSocket::SocketError& err, int id)
{
	onLog("Client: " + std::to_string(id) + " has detected error: " + std::to_string(err));
}

void Network::OnHostConnectError(const QAbstractSocket::SocketError& err)
{
	onLog("Host has detected error: " + std::to_string(err));
}

void Network::OnSelfHostFound()
{
	onLog("Client has found Server!");
}

void Network::OnSelfStateChanged(const QAbstractSocket::SocketState& state)
{
	onLog("Client has changed State: " + std::to_string(state));
}

void Network::OnSelfBytesWritten(int bytes)
{
	onLog("Client has written[bytes]: " + std::to_string(bytes));
}

void Network::OnSelfConnected()
{
	onLog("Client has Connected to Host!");
}

void Network::OnSelfDisconnect()
{
	onLog("Client has Disconnected from Host!");
}

void Network::OnClientReceivedData(int id)
{
	if (m_sockets[id]->bytesAvailable() > 0)
	{
		auto qreadsize = m_sockets[id]->read(HEADERSIZE);
		QDataStream sizestream{ qreadsize };
		int size{};
		sizestream >> size;
		auto qdata = m_sockets[id]->read(size);
		std::vector<char> data{ std::begin(qdata), std::end(qdata) };
		onLog("Data Received on Client: " + std::to_string(id));
		onData(data);
	}
}

void Network::OnClientConnected(int id)
{
	onLog("Client: " + std::to_string(id) + " has connected to Host!");
}

void Network::OnClientDisconnect(int id)
{
	onLog("Client: " + std::to_string(id) + " has disconnected from Host!");
}

void Network::OnSelfClientConnectError(const QAbstractSocket::SocketError& err)
{
	onLog("Client has detected error: " + std::to_string(err));
}

void Network::OnClientHostFound(int id)
{
	onLog("Client: " + std::to_string(id) + " has found Host!");
}

void Network::OnClientStateChanged(const QAbstractSocket::SocketState& state, int id)
{
	onLog("Client: " + std::to_string(id) + " has changed state: " + std::to_string(state));
}

void Network::OnClientBytesWritten(int bytes, int id)
{
	onLog("Client: " + std::to_string(id) + " has written[bytes]: " + std::to_string(bytes));
}
