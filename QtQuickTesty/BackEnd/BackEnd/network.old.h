#pragma once
#include "datatypes.h"
#include "backend_global.h"

const int PORT = 4242;

struct Network : public QObject
{
	//funcs from flow design pls
	explicit Network(QObject* parent = nullptr);
	std::string GenerateLobbyCode();
	void StartServer();
	void ConnectToServer(const std::string&);
	~Network();

	Event<const std::string&> onLog;
	Event<const std::string&> onDataReceived;

public slots:
	void NewConnection();
	void ReadyRead();
	void ConnectionError(QAbstractSocket::SocketError);
	void Connected();

private:
	QTcpServer server{};
	QTcpSocket socket{};
	std::vector<QTcpSocket*> connections;
};