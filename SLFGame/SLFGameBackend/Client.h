#pragma once
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"
#include "DataTypes.h"
#include "ClientSource.h"

class Client : public ClientSource, public QObject
{
public:
	Client();
	virtual ~Client();

	std::string GenerateLobbyCode();
	void ConnectToServer(const LobbyCode&);
	void WriteToHost(const ByteStream&);

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
};