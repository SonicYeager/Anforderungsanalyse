#pragma once
#include "backend_global.h"
#include "datatypes.h"

class Server : public QObject
{
public:
	Server();
	virtual ~Server();

	std::string GenerateLobbyCode();
	LobbyCode StartServer();
	void WriteTo(const ByteStream&, int);
	void Broadcast(const ByteStream&);

	Event<int> onNewConnection;
	Event<ByteStream, int> onClientData;
	Event<std::string> onLog;

public slots:

	//TcpServer
	void OnNewConnection();
	void OnHostConnectError(const QAbstractSocket::SocketError&);

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
	std::vector<std::unique_ptr<QTcpSocket>> m_sockets;
};