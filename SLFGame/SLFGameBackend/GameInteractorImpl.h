#pragma once
#include "GameInteractor.h"

#include "GameLogic.h"
#include "RandomGenRessource.h"
#include "DataOperationLogic.h"
#include "ClientInteractor.h"
#include "ServerInteractor.h"

class GameInteractorImpl : public GameInteractor
{
public:
	explicit GameInteractorImpl(
		GameLogic*,
		RandomGenRessource*,
		DataOperationLogic*,
		ClientInteractor*,
		ServerInteractor*
	);

	//ui client
	void HostLobby(const std::string&) override;
	void JoinLobby(const LobbyCode&, const std::string&) override;
	void LobbyChanged(const std::string& cats, const std::string& timeout, const std::string& rounds) override;
	void ChatMessageReceived(const std::string& sender, const std::string& text)override;
	void StateChangeTriggered(const STATE&) override;
	void AnswersReceived(const std::vector<std::string>&) override;

	//server
	virtual void AddAnswers(const PlayerAnswers&) override;
	virtual void AddPlayer(const PlayerStats&) override;
	virtual void SetGameSettings(const HandleGameSettings&) override;
	virtual void RemovePlayer(const int&) override;
	virtual void ChangeGameState(const GameState&) override;

private:
	GameLogic* m_pGame;
	RandomGenRessource* m_pRandGen;
	DataOperationLogic* m_pGameStatsOperation;
	ClientInteractor* m_pClient;
	ServerInteractor* m_pServer;

	GameStats m_GameStats;
	int m_answerCount{};
};

