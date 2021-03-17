#pragma once
#include "GameInteractor.h"

#include "GameLogic.h"
#include "RandomGenRessource.h"
#include "DataOperationLogic.h"
#include "ServerInteractor.h"
#include "SLFParser.h"

class GameInteractorImpl : public GameInteractor
{
public:
	explicit GameInteractorImpl(
		GameLogic*,
		RandomGenRessource*,
		DataOperationLogic*,
		ServerInteractor*
	);

	//server
	void RemovePlayer(const int&)override;
	void AddAnswers(int, const std::vector<std::string>&)override;
	void AddPlayer(int, const std::string&) override;
	void SetGameSettings(const LobbySettings&) override;
	void ChangeGameState(const STATE&) override;
	void SetLobbyCode(const LobbyCode&) override;
	void ToggleVote(const Index&) override;

	GameStats m_GameStats;

private:
	//helper funcs
	HandleGameSettings CreateHandleGameSettings();
	void HandleGameState(const STATE& state);
	void SendUpdatedLobbySettings();

	GameLogic* m_pGame;
	RandomGenRessource* m_pRandomGenerator;
	DataOperationLogic* m_pDataOperation;
	SLFParser m_Parser;
	ServerInteractor* m_pServer;

	int m_answerGatheredCounter{};
};

