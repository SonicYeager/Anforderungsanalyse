#pragma once
#include "NetworkSource.h"
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"

class GameNetwork : public NetworkSource, public QObject
{
public:
	
	explicit	GameNetwork			(QObject* parent = nullptr);
				~GameNetwork		();

	std::string GenerateLobbyCode	()								override;
	void		StartServer			()								override;
	void		ConnectToServer		(const std::string&)			override;
	void		Write				(const NetworkData&, int)		override;
	void		Broadcast			(const NetworkData&)			override;
	void		WriteToHost			(const NetworkData&)			override;

public slots:

	void NewConnection();
	void ReadyRead();

private:
	QTcpServer					m_server;
	QHostAddress				m_serverAddress = QHostAddress::Any;
	QTcpSocket					m_socket;
	std::vector<QTcpSocket*>	m_connections;
	int							m_port			= 3200;

};