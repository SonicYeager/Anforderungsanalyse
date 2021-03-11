#pragma once
#include "Server.h"

Server::Server()
{
	QObject::connect(&m_server, &QTcpServer::newConnection, this, &Server::OnNewConnection);
	QObject::connect(&m_server, &QTcpServer::acceptError, this, &Server::OnHostConnectError);

	m_server.moveToThread(&serverThread);
	serverThread.start();
}

Server::~Server()
{
	serverThread.exit();
	serverThread.quit();
	serverThread.wait();
}

std::string Server::GenerateLobbyCode()
{
	const QHostAddress& localhost = QHostAddress(QHostAddress::LocalHost);
	for (const QHostAddress& address : QNetworkInterface::allAddresses())
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
			return address.toString().toStdString();
	}
	return localhost.toString().toStdString();
}

LobbyCode Server::StartServer()
{
	auto checker = m_server.listen(QHostAddress::Any, PORT);
	std::string b = checker == true ? "True" : "False";
	onLog("Server Listen: " + b);
	auto lobbyCode = GenerateLobbyCode();
	return lobbyCode;
}

void Server::WriteTo(const ByteStream& data, int id)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	QVector<char> datavec{ std::begin(data), std::end(data) };
	sizestream << datavec;
	m_sockets[id]->write(qdata);
	onLog("Data has been send to client: " + std::to_string(id));
}

void Server::Broadcast(const ByteStream& data)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	
	auto size = std::to_string(data.size());
	ByteStream sizeStream{ std::begin(size), std::end(size) };

	sizestream.writeBytes(sizeStream.data(), HEADERSIZE);
	sizestream.writeBytes(data.data(), data.size());
	for (auto& socket : m_sockets)
		socket.second->write(qdata);
	onLog("Data has been Broadcasted!");
}

void Server::OnNewConnection()
{
	auto conn = m_server.nextPendingConnection();
	auto id = m_sockets.size();
	m_sockets.emplace(id, conn);

	QObject::connect(&*m_sockets[id], &QTcpSocket::connected,		[this, id]() {OnClientConnected(id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::disconnected,	[this, id]() {OnClientDisconnect(id); });
	QObject::connect(&*m_sockets[id], &QIODevice::readyRead,		[this, id]() {OnClientReceivedData(id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::errorOccurred,	[this, id](const QAbstractSocket::SocketError& err) {OnClientClientConnectError(err, id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::bytesWritten,	[this, id](int written) {OnClientBytesWritten(written, id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::hostFound,		[this, id]() {OnClientHostFound(id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::stateChanged,	[this, id](const QAbstractSocket::SocketState& state) {OnClientStateChanged(state, id); });
	QObject::connect(&*m_sockets[id], &QTcpSocket::destroyed,		[this, id](QObject* obj) {OnDestroyed(obj, id); });

	onLog("New Connection of Client: " + std::to_string(id));
	onNewConnection(id);
}

void Server::OnClientClientConnectError(const QAbstractSocket::SocketError& err, int id)
{
	onLog("Client: " + std::to_string(id) + " has detected error: " + std::to_string(err));
}

void Server::OnHostConnectError(const QAbstractSocket::SocketError& err)
{
	onLog("Host has detected error: " + std::to_string(err));
}

void Server::OnClientReceivedData(int id)
{
	if (m_sockets[id]->bytesAvailable() > 0)
	{
		auto qreadsize = m_sockets[id]->read(HEADERSIZE);
		QDataStream sizestream{ &qreadsize, QIODevice::ReadOnly};
		sizestream.setVersion(QDataStream::Qt_5_15);

		int size{};
		sizestream >> size;
		auto qdata = m_sockets[id]->read(size);
		std::vector<char> data{ std::begin(qdata), std::end(qdata) };
		onLog("Data Received on Client: " + std::to_string(id));
		onClientData(data, id);
	}
}

void Server::OnClientConnected(int id)
{
	onLog("Client: " + std::to_string(id) + " has connected to Host!");
}

void Server::OnClientDisconnect(int id)
{
	onLog("Client: " + std::to_string(id) + " has disconnected from Host!");
	m_sockets[id]->blockSignals(true);
	m_sockets[id]->disconnect(SIGNAL(&QTcpSocket::connected));
	m_sockets[id]->disconnect(SIGNAL(&QTcpSocket::disconnected));
	m_sockets[id]->disconnect(SIGNAL(&QIODevice::readyRead));
	m_sockets[id]->disconnect(SIGNAL(&QTcpSocket::errorOccurred));
	m_sockets[id]->disconnect(SIGNAL(&QTcpSocket::bytesWritten));
	m_sockets[id]->disconnect(SIGNAL(&QTcpSocket::hostFound));
	m_sockets[id]->disconnect(SIGNAL(&QTcpSocket::stateChanged));
	m_sockets[id]->deleteLater();
}

void Server::OnClientHostFound(int id)
{
	onLog("Client: " + std::to_string(id) + " has found Host!");
}

void Server::OnClientStateChanged(const QAbstractSocket::SocketState& state, int id)
{
	onLog("Client: " + std::to_string(id) + " has changed state: " + std::to_string(state));
}

void Server::OnClientBytesWritten(int bytes, int id)
{
	onLog("Client: " + std::to_string(id) + " has written[bytes]: " + std::to_string(bytes));
}

void Server::OnDestroyed(QObject* obj, int id)
{
	onLog("Client Socket: " + std::to_string(id) + " was deleted!");
	m_sockets.erase(id);
}
