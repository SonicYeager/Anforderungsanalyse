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
	ByteStream WaitForData();
	ByteStream WaitForData(int);
	void WaitForNewConnection();
	void WaitForConnection();

	Event<> onNewConnection;
	Event<std::string> onLog;
	Event<ByteStream> onData;

public slots:

	//TcpServer
	void OnNewConnection();
	void OnHostConnectError(const QAbstractSocket::SocketError&);
	//TcpSSocket
	void OnSelfReceivedData();
	void OnSelfConnected();
	void OnSelfDisconnect();
	void OnSelfClientConnectError(const QAbstractSocket::SocketError&);
	void OnSelfHostFound();
	void OnSelfStateChanged(const QAbstractSocket::SocketState&);
	void OnSelfBytesWritten(int);
	//TcpSockets
	void OnClientReceivedData(int);
	void OnClientConnected(int);
	void OnClientDisconnect(int);
	void OnClientClientConnectError(const QAbstractSocket::SocketError&, int);
	void OnClientHostFound(int);
	void OnClientStateChanged(const QAbstractSocket::SocketState&, int);
	void OnClientBytesWritten(int, int);

private:
	QThread serverThread;
	QTcpServer m_server;
	QTcpSocket m_serverSocket;
	std::vector<std::unique_ptr<QTcpSocket>> m_sockets;
};