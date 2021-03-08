#pragma once
#include "NetworkSource.h"
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"

const int PORT = 5200;

class Network : public NetworkSource, public QObject
{
public:
	Network();

	virtual LobbyCode StartServer() override;
	virtual void ConnectToServer(const LobbyCode&) override;
	virtual void WriteTo(const ByteStream&, int) override;
	virtual void WriteToHost(const ByteStream&) override;
	virtual void Broadcast(const ByteStream&) override;
	virtual ByteStream ReceiveData() override;
	virtual ByteStream ReceiveData(int) override;

public slots:
	void OnNewConnection();
	void OnSelfReceivedData();
	void OnError();
	void OnConnected();

private:
	void OnReceivedData(int);
	std::string GenerateLobbyCode(); //pls remove
	QTcpServer m_server;
	QTcpSocket m_serverSocket;
	std::vector<std::unique_ptr<QTcpSocket>> m_sockets;
};