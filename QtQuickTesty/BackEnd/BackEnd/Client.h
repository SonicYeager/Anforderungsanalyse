#pragma once
#include "backend_global.h"
#include "datatypes.h"

class Client : public QObject
{
public:
	Client();

	std::string GenerateLobbyCode();
	void ConnectToServer(const LobbyCode&);
	void WriteToHost(const ByteStream&);

	Event<std::string> onLog;

	Event<ByteStream> onData;

public slots:

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