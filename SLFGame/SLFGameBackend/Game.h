#pragma once
#include "GameLogic.h"

class Game : public GameLogic
{
public:
	void	CalculatePoints		(const DDDVector&)	override;
	void	CheckGameFinished	(Event<const std::string&, const Letters&> onNextRound, Event<const std::map<int, PlayerStats>&> onFinalScores)		override;
	void    HandleGameState(const STATE& state, Event<const std::string&, const Letters&> onSetupRound, Event<const std::map<int, PlayerStats>&> onFinalScores, Event<GameState> onStandart) override;
	HandleGameSettings CreateHandleGameSettings() override;

	GameStats& GetGameStats() override;

	void AddPlayer(int, const std::string&) override;
	void AddAnswers(int id, const std::vector<std::string>& answers, Event<GameStats>) override;
	void RemovePlayer(int id) override;
	void SetGameSettings(const std::string& cat, const std::string& timeout, int maxRound) override;
	void SetGameState(STATE) override;
	void SetLobbyCode(const LobbyCode&) override;
	void ToggleVote(const Index& index) override;
	void SetupRound(const Categories&, const Letter&, Event<RoundSetup, const GameStats&> onBroadcast) override;
	void SetVotesFalseForEmptyAnswers() override;

	GameStats m_GameStats;
	void ClearPlayerAnswers();
private:

	int m_answerGatheredCounter{};

	void ResetGame();
	void CheckAllAnswersRecived(Event<GameStats> onTrue);
	void HandOutPointsForCategory(int, int, std::vector<bool>);
};