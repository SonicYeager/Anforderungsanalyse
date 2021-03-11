#pragma once
#include "slfgamebackendqt_global.h"
#include "DataTypes.h"
#include "ServerSource.h"

class Server : public ServerSource, public QObject
{
public:
	Server();
	virtual ~Server();

	std::string GenerateLobbyCode();
	LobbyCode StartServer();
	void WriteTo(const ByteStream&, int);
	void Broadcast(const ByteStream&);

private slots:

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
	std::atomic<int> m_counter{};
	QThread serverThread;
	QTcpServer m_server;
	std::map<int, std::shared_ptr<QTcpSocket>> m_sockets;
};