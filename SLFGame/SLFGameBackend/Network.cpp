#pragma once
#include "Network.h"
#include <fstream>

Network::Network()
{
	QObject::connect(&m_server, &QTcpServer::newConnection, this, &Network::OnNewConnection);
	QObject::connect(&m_serverSocket, &QIODevice::readyRead, this, &Network::OnSelfReceivedData);
	QObject::connect(&m_serverSocket, &QTcpSocket::errorOccurred, this, &Network::OnError);
	QObject::connect(&m_serverSocket, &QTcpSocket::connected, this, &Network::OnConnected);
}

std::string Network::GenerateLobbyCode()
{
	const QHostAddress& localhost = QHostAddress(QHostAddress::LocalHost);
	for (const QHostAddress& address : QNetworkInterface::allAddresses()) 
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
			return address.toString().toStdString();
	}
}

LobbyCode Network::StartServer()
{
	auto checker = m_server.listen(QHostAddress::Any, PORT);
	return GenerateLobbyCode();
}

void Network::ConnectToServer(const LobbyCode& code)
{
	m_serverSocket.connectToHost(QHostAddress(code.c_str()), PORT, QIODeviceBase::ReadWrite);
}

void Network::WriteTo(const ByteStream& data, int id)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	sizestream << sizeof(data);
	sizestream.writeBytes(data.data(), data.size());
	m_sockets[id]->write(qdata);
}

void Network::WriteToHost(const ByteStream& data)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	sizestream << sizeof(data);
	sizestream.writeBytes(data.data(), data.size());
	m_serverSocket.write(qdata);
}

void Network::Broadcast(const ByteStream& data)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QDataStream::WriteOnly };
	sizestream << sizeof(data);
	sizestream.writeBytes(data.data(), data.size());
	for (const auto& socket : m_sockets)
		socket->write(qdata);
}

ByteStream Network::ReceiveData()
{
	m_serverSocket.waitForReadyRead();
	auto qreadsize = m_serverSocket.read(HEADERSIZE);
	QDataStream sizestream{ qreadsize };
	int size{};
	sizestream >> size;
	auto qdata = m_serverSocket.read(size);
	std::vector<char> data{ std::begin(qdata), std::end(qdata) };
	return data;
}

ByteStream Network::ReceiveData(int id)
{
	m_sockets[id]->waitForReadyRead();
	auto qreadsize = m_sockets[id]->read(HEADERSIZE);
	QDataStream sizestream{ qreadsize };
	int size{};
	sizestream >> size;
	auto qdata = m_sockets[id]->read(size);
	std::vector<char> data{ std::begin(qdata), std::end(qdata) };
	return data;
}

void Network::OnNewConnection()
{
	std::fstream f{ "error_log.txt", std::fstream::in | std::fstream::out | std::fstream::app };
	f << "New Connection" << std::endl;
	auto conn = m_server.nextPendingConnection();
	m_sockets.push_back(std::unique_ptr<QTcpSocket>(conn));
	auto id = m_sockets.size()-1;
	QObject::connect(&*m_sockets[id], &QIODevice::readyRead, [this, id]() {OnReceivedData(id); });
	onNewConnection();
}

void Network::OnSelfReceivedData()
{
	std::fstream f{ "error_log.txt", std::fstream::in | std::fstream::out | std::fstream::app };
	f << "Data Self Received" << std::endl;
	if (m_serverSocket.bytesAvailable() > 0)
	{
		auto qreadsize = m_serverSocket.read(HEADERSIZE);
		QDataStream sizestream{ qreadsize };
		int size{};
		sizestream >> size;
		auto qdata = m_serverSocket.read(size);
		std::vector<char> data{ std::begin(qdata), std::end(qdata) };
		onReceivedData(data);
	}
}

void Network::OnError()
{
	//TODO
	std::fstream f{"error_log.txt", std::fstream::in | std::fstream::out | std::fstream::app };
	f << "Connection Error" << std::endl;
}

void Network::OnConnected()
{
	//TODO
	std::fstream f{ "error_log.txt", std::fstream::in | std::fstream::out | std::fstream::app };
	f << "Connection Succ" << std::endl;
}

void Network::OnReceivedData(int id)
{
	std::fstream f{ "error_log.txt", std::fstream::in | std::fstream::out | std::fstream::app };
	f << "Data Received" << std::endl;
	if (m_sockets[id]->bytesAvailable() > 0)
	{
		auto qreadsize = m_sockets[id]->read(HEADERSIZE);
		QDataStream sizestream{ qreadsize };
		int size{};
		sizestream >> size;
		auto qdata = m_sockets[id]->read(size);
		std::vector<char> data{ std::begin(qdata), std::end(qdata) };
		onReceivedData(data);
	}
}
