#pragma once
#include "NetworkSource.h"

class GameNetwork : public NetworkSource, public QObject
{
public:
	
	explicit	GameNetwork			(QObject* parent = nullptr);
				~GameNetwork		();

	std::string GenerateLobbyCode	()								override;
	void		StartServer			()								override;
	void		ConnectToServer		(const std::string&)			override;
	void		Write				(const QByteArray&, int)		override;
	void		Broadcast			(const QByteArray&)			override;
	void		WriteToHost			(const QByteArray&)			override;

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