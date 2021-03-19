#pragma once
#include <vector>
#include "DataTypes.h"
#include "Messages.h"

using namespace Messages;

class GameLogic
{
public:
	virtual			~GameLogic() = default;

	virtual void	CalculatePoints		(const DDDVector&) = 0;
	virtual void	CheckGameFinished	(Event<const std::string&, const Letters&>) = 0;
	virtual void	HandleGameState(const STATE& state, Event<const std::string&, const Letters&> onSetupRound, Event<GameState> onStandart) = 0;
	virtual HandleGameSettings CreateHandleGameSettings() = 0;
	virtual void	SetVotesFalseForEmptyAnswers() = 0;

	virtual GameStats& GetGameStats() = 0;

	//datamods
	virtual void AddPlayer(int, const std::string&) = 0;
	virtual void AddAnswers(int id, const std::vector<std::string>& answers, Event<GameStats>) = 0;
	virtual void RemovePlayer(int id) = 0;
	virtual void SetGameSettings(const std::string& cat, const std::string& timeout, int maxRound) = 0;
	virtual void SetGameState(STATE) = 0;
	virtual void SetLobbyCode(const LobbyCode&) = 0;
	virtual void ToggleVote(const Index& index) = 0;
	virtual void SetupRound(const Categories&, const Letter&, Event<RoundSetup, const GameStats&> onBroadcast) = 0;


	Event<> onGameOver;
	Event<> onPrepareNextRound;
};