#pragma once
#include "framework.h"
#include "Interactor.h"
#include "DataOperationLogic.h"
#include "DataTypes.h"
#include "RandomGenRessource.h"
#include "NetworkSource.h"
#include "SLFParser.h"
#include "GameLogic.h"
#include "Serializer.h"
#include <map>

class GameInteractor : public Interactor
{
public:
	explicit	GameInteractor	(RandomGenRessource*, DataOperationLogic*, GameLogic*, NetworkSource*, SLFParser*, Serializer*);
	void		PrepareGame		(const std::string& cats, const std::string& roundTime, const std::string& roundCount) override;
	void		PrepareOverview	(const std::vector<std::string>&, int) override;
	void		EndRound		(const std::vector<DECISION>&, int) override;
	void		HostGame		(const std::string&) override;
	void		JoinGame		(const std::string& lobbyCode, const std::string& playerName) override;

	GameStats	m_GameStats;

private:
	RandomGenRessource* m_pRandomGenerator;
	DataOperationLogic* m_pDataOperation;
	GameLogic*			m_pGame;
	NetworkSource*		m_pNetwork;
	SLFParser*			m_pParser;
	Serializer*			m_pSerialzer;

	std::map<HEADER, Event<NetworkData>> onRead;
};

