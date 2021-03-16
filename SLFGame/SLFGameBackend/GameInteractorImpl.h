#pragma once
#include "GameInteractor.h"

#include "GameLogic.h"
#include "RandomGenRessource.h"
#include "DataOperationLogic.h"
#include "ClientInteractor.h"
#include "ServerInteractor.h"
#include "SLFParser.h"

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
	void RemovePlayer(const int&)override;
	void AddAnswers(int, const std::vector<std::string>&)override;
	void AddPlayer(int, const PlayerStats&) override;
	void SetGameSettings(const LobbySettings&) override;
	void ChangeGameState(const STATE&) override;
	void SetLobbyCode(const LobbyCode&) override;

private:
	//helper funcs
	HandleGameSettings CreateHandleGameSettings();
	void HandleGameState(const STATE& state);
	void SendUpdatedLobbySettings();

	GameLogic* m_pGame;
	RandomGenRessource* m_pRandomGenerator;
	DataOperationLogic* m_pDataOperation;
	ClientInteractor* m_pClient;
	ServerInteractor* m_pServer;
	SLFParser m_Parser;

	GameStats m_GameStats;
	int m_answerGatheredCounter{};
};

