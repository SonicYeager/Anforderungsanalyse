#pragma once
#include "DataTypes.h"

class ClientInteractor
{
public:
	virtual void EndRound(const std::vector<DECISION>& decisions) = 0;
	virtual void HostLobby(const std::string&) = 0;
	virtual void JoinLobby(const LobbyCode&, const std::string&) = 0;
	virtual void LobbyChanged(const std::string& cats, const std::string& timeout, const std::string& rounds) = 0;
	virtual ~ClientInteractor() = default;

	//ui events
	Event<GameStats> onUpdateLobby;
	Event<GameStats> onGameOver;
	Event<int> onReceivedID;
	Event<LobbyCode> onSetLobbyCode;
	Event<LobbySettings> onUpdateLobbySettings;
	Event<STATE> onGameState;

	//server events
	Event<> onStartServer;
};