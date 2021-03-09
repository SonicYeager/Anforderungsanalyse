#pragma once
#include "backend_global.h"

const int PORT = 4242;

class Network : public NetworkSource, public QObject
{
public:
	Network();

	LobbyCode StartServer() override;
	void ConnectToServer(const LobbyCode&) override;
	void WriteTo(const ByteStream&, int) override;
	void WriteToHost(const ByteStream&) override;
	void Broadcast(const ByteStream&) override;
	ByteStream ReceiveData() override;
	ByteStream ReceiveData(int) override;
	void WaitForNewConnection() override;

public slots:
	void OnNewConnection();
	void OnSelfReceivedData();
	void OnClientConnectError(const QAbstractSocket::SocketError&);
	void OnHostConnectError(const QAbstractSocket::SocketError&);
	void OnConnected();

private:
	void OnReceivedData(int);
	std::string GenerateLobbyCode(); //pls remove
	QThread serverThread;
	QTcpServer m_server;
	QTcpSocket m_serverSocket;
	std::vector<std::unique_ptr<QTcpSocket>> m_sockets;
};