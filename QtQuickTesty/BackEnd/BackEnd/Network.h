#pragma once
#include "backend_global.h"
#include "datatypes.h"

const int PORT = 4242;
const int HEADERSIZE = sizeof(int);

class Network : public QObject
{
public:
	Network();

	std::string GenerateLobbyCode();
	LobbyCode StartServer();
	void ConnectToServer(const LobbyCode&);
	void WriteTo(const ByteStream&, int);
	void WriteToHost(const ByteStream&);
	void Broadcast(const ByteStream&);
	ByteStream ReceiveData();
	ByteStream ReceiveData(int);
	void WaitForNewConnection();

	Event<std::string> onLog;
	Event<ByteStream> onData;

public slots:
	void OnNewConnection();
	void OnSelfReceivedData();
	void OnReceivedData(int);
	void OnClientConnectError(const QAbstractSocket::SocketError&);
	void OnHostConnectError(const QAbstractSocket::SocketError&);
	void OnConnected();

private:
	QThread serverThread;
	QTcpServer m_server;
	QTcpSocket m_serverSocket;
	std::vector<std::unique_ptr<QTcpSocket>> m_sockets;
};