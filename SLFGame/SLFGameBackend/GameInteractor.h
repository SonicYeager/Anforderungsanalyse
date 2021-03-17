#pragma once
#include "DataTypes.h"
#include "Messages.h"

using namespace Messages;

class GameInteractor
{
public:
	~GameInteractor() = default;

	//server
	virtual void RemovePlayer(const int&) = 0;
	virtual void AddAnswers(int, const std::vector<std::string>&) = 0;
	virtual void AddPlayer(int, const std::string&) = 0;
	virtual void SetGameSettings(const LobbySettings&) = 0;
	virtual void ChangeGameState(const STATE&) = 0;
	virtual void SetLobbyCode(const LobbyCode&) = 0;
	virtual void ToggleVote(const Index&) = 0;

};