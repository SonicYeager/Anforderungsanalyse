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

	virtual void AddAnswers(const PlayerAnswers&) = 0;

private:
	GameLogic* m_pGame;
	RandomGenRessource* m_pRandGen;
	DataOperationLogic* m_pGameStatsOperation;
	ClientInteractor* m_pClient;
	ServerInteractor* m_pServer;

	GameStats m_GameStats;
	int m_answerCount{};
};

