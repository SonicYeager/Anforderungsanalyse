#pragma once
#include "Server.h"

Server::Server()
{
	m_server.moveToThread(&serverThread);

	QObject::connect(&m_server, &QTcpServer::newConnection, this, &Server::OnNewConnection);
	QObject::connect(&m_server, &QTcpServer::acceptError, this, &Server::OnHostConnectError);

	serverThread.start(QThread::Priority::TimeCriticalPriority);
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
	//onLog("Server Listen: " + b);
	auto lobbyCode = GenerateLobbyCode();
	return lobbyCode;
}

void Server::StartListening()
{
	m_server.listen(QHostAddress::Any, PORT);
}

void Server::StopListening()
{
	m_server.close();
}

void Server::WriteTo(const ByteStream& data, int id)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	QVector<char> datavec{ std::begin(data), std::end(data) };
	sizestream << datavec;
	m_sockets[id]->write(qdata);
	//onLog("Data has been send to client: " + std::to_string(id));
}

void Server::Broadcast(const ByteStream& data)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	QVector<char> datavec{ std::begin(data), std::end(data) };
	sizestream << datavec;
	for (const auto& socket : m_sockets)
		socket.second->write(qdata);
	//onLog("Data has been Broadcasted!");
}

void Server::Reset()
{
	for (auto& socket : m_sockets)
	{ 
		socket.second->close();
	}
}

void Server::OnNewConnection()
{
	auto conn = m_server.nextPendingConnection();
	int id = m_counter.fetch_add(1);
	m_sockets.emplace(id, std::shared_ptr<QTcpSocket>(conn, [](QTcpSocket* sock) { sock->deleteLater(); }));

	QObject::connect(m_sockets[id].get(), &QTcpSocket::connected, [this, id]() {OnClientConnected(id); });
	QObject::connect(m_sockets[id].get(), &QTcpSocket::disconnected, [this, id]() {OnClientDisconnect(id); });
	QObject::connect(m_sockets[id].get(), &QIODevice::readyRead, [this, id]() {OnClientReceivedData(id); });
	QObject::connect(m_sockets[id].get(), &QTcpSocket::errorOccurred, [this, id](const QAbstractSocket::SocketError& err) {OnClientClientConnectError(err, id); });
	QObject::connect(m_sockets[id].get(), &QTcpSocket::bytesWritten, [this, id](int written) {OnClientBytesWritten(written, id); });
	QObject::connect(m_sockets[id].get(), &QTcpSocket::hostFound, [this, id]() {OnClientHostFound(id); });
	QObject::connect(m_sockets[id].get(), &QTcpSocket::stateChanged, [this, id](const QAbstractSocket::SocketState& state) {OnClientStateChanged(state, id); });

	//onLog("New Connection of Client: " + std::to_string(id));
	onNewConnection(id);
}

void Server::OnClientClientConnectError(const QAbstractSocket::SocketError& err, int id)
{
	//onLog("Client: " + std::to_string(id) + " has detected error: " + std::to_string(err));
}

void Server::OnHostConnectError(const QAbstractSocket::SocketError& err)
{
	//onLog("Host has detected error: " + std::to_string(err));
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
		//onLog("Data Received on Client: " + std::to_string(id));
		onClientData(data, id);
	}
}

void Server::OnClientConnected(int id)
{
	//onLog("Client: " + std::to_string(id) + " has connected to Host!");
}

void Server::OnClientDisconnect(int id)
{
	//onLog("Client: " + std::to_string(id) + " has disconnected from Host!");

	m_sockets.erase(id);
	onClientDisconnect(id);
}

void Server::OnClientHostFound(int id)
{
	//onLog("Client: " + std::to_string(id) + " has found Host!");
}

void Server::OnClientStateChanged(const QAbstractSocket::SocketState& state, int id)
{
	//onLog("Client: " + std::to_string(id) + " has changed state: " + std::to_string(state));
}

void Server::OnClientBytesWritten(int bytes, int id)
{
	//onLog("Client: " + std::to_string(id) + " has written[bytes]: " + std::to_string(bytes));
}
