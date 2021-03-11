#pragma once
#include "Client.h"


Client::Client()
{
	QObject::connect(&m_socket, &QTcpSocket::connected, this, &Client::OnSelfConnected);
	QObject::connect(&m_socket, &QAbstractSocket::disconnected, this, &Client::OnSelfDisconnect);
	QObject::connect(&m_socket, &QIODevice::readyRead, this, &Client::OnSelfReceivedData);
	QObject::connect(&m_socket, &QTcpSocket::errorOccurred, this, &Client::OnSelfClientConnectError);
	QObject::connect(&m_socket, &QTcpSocket::bytesWritten, this, &Client::OnSelfBytesWritten);
	QObject::connect(&m_socket, &QTcpSocket::hostFound, this, &Client::OnSelfHostFound);
	QObject::connect(&m_socket, &QTcpSocket::stateChanged, this, &Client::OnSelfStateChanged);
}

Client::~Client()
{
	onLog = [](const std::string& text) { auto temp = text; temp.clear(); };
	m_socket.disconnectFromHost();
	m_socket.close();
}

std::string Client::GenerateLobbyCode()
{
	const QHostAddress& localhost = QHostAddress(QHostAddress::LocalHost);
	for (const QHostAddress& address : QNetworkInterface::allAddresses())
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
			return address.toString().toStdString();
	}
	return localhost.toString().toStdString();
}

void Client::ConnectToServer(const LobbyCode& code)
{
	m_socket.connectToHost(QHostAddress(code.c_str()), PORT, QIODeviceBase::ReadWrite);
	onLog("Attempting to connect to Host...");
}

void Client::WriteToHost(const ByteStream& data)
{
	QByteArray qdata{};
	QDataStream sizestream{ &qdata, QIODevice::WriteOnly };
	sizestream.setVersion(QDataStream::Qt_5_15);
	QVector<char> datavec{std::begin(data), std::end(data)};
	sizestream << datavec;
	m_socket.write(qdata);
	onLog("Data has been send to Host!");
}

void Client::OnSelfReceivedData()
{
	if (m_socket.bytesAvailable() > 0)
	{
		auto qreadsize = m_socket.read(HEADERSIZE);
		QDataStream sizestream{ &qreadsize, QIODevice::ReadOnly };
		sizestream.setVersion(QDataStream::Qt_5_15);
		int size{};
		sizestream >> size;
		auto qdata = m_socket.read(size);
		std::vector<char> data{ std::begin(qdata), std::end(qdata) };
		onLog("Data Received!");
		onData(data);
	}
}

void Client::OnSelfHostFound()
{
	onLog("Client has found Server!");
}

void Client::OnSelfStateChanged(const QAbstractSocket::SocketState& state)
{
	onLog("Client has changed State: " + std::to_string(state));
}

void Client::OnSelfBytesWritten(int bytes)
{
	onLog("Client has written[bytes]: " + std::to_string(bytes));
}

void Client::OnSelfConnected()
{
	onLog("Client has Connected to Host!");
}

void Client::OnSelfDisconnect()
{
	onLog("Client has Disconnected from Host!");
}

void Client::OnSelfClientConnectError(const QAbstractSocket::SocketError& err)
{
	onLog("Client has detected error: " + std::to_string(err));
}
