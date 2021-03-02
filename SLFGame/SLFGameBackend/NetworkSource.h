#pragma once
#include <string>
#include "DataTypes.h"
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"

class NetworkSource 
{
public:
	virtual ~NetworkSource() = default;

	virtual std::string GenerateLobbyCode()					= 0;
	virtual void		StartServer()						= 0;
	virtual void		ConnectToServer(const std::string&) = 0;
	virtual void		Broadcast(const QDataStream&)		= 0;
	virtual void		Write(const QDataStream&, int)		= 0;
	virtual void		WriteToHost(const QDataStream&)		= 0;

	Event<int> onNewConnection;
	Event<const NetworkData&> onReadyRead;
};