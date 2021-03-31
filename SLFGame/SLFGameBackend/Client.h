#pragma once
#include "slfgamebackendqt_global.h"
#include "DataTypes.h"
#include "ClientSource.h"

class Client : public ClientSource, public QObject
{
public:
	Client();
	virtual ~Client();

	std::string GenerateLobbyCode() override;
	void ConnectToServer(const LobbyCode&) override;
	void DisconnectFromServer() override;
	void WriteToHost(const ByteStream&) override;

private slots:

	void OnSelfReceivedData();
	void OnSelfConnected();
	void OnSelfDisconnect();
	void OnSelfClientConnectError(const QAbstractSocket::SocketError&);
	void OnSelfHostFound();
	void OnSelfStateChanged(const QAbstractSocket::SocketState&);
	void OnSelfBytesWritten(int);

private:
	QTcpSocket m_socket;
	QThread clientThread;
};