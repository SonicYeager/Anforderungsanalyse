#include "GameInteractorImpl.h"

GameInteractorImpl::GameInteractorImpl(
	GameLogic* gl,
	RandomGenRessource* rgr,
	DataOperationLogic* dol,
	ClientInteractor* ci,
	ServerInteractor* si)
	:
	m_pGame(gl),
	m_pRandGen(rgr),
	m_pGameStatsOperation(dol),
	m_pClient(ci),
	m_pServer(si)
{
	//link both inter to each other
	//link server to own data ops
}
