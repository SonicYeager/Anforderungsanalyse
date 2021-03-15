#include "ServerInteractorImpl.h"

ServerInteractorImpl::ServerInteractorImpl(
	ServerSource* s, 
	SerializerSource* ss, 
	MessageHandlerLogic* msg,
	RandomGenRessource* gen,
	DataOperationLogic* op,
	GameLogic* game,
	SLFParser* p
) :
	m_pServer(s),
	m_pSerializer(ss),
	m_pMsgHandler(msg),
	m_pRandomGenerator(gen),
	m_pDataOperation(op),
	m_pGame(game),
	m_pParser(p)
{
	//m_server->onLog = [this](const std::string& text) {OnLog(text); };
	m_pServer->onNewConnection = [this](int id) {OnNewConnection(id); };
	m_pServer->onClientData = [this](const ByteStream& stream, int id) { OnData(stream, id); };
	m_pServer->onClientDisconnect = [this](int id) { OnDisconnect(id); };

	m_pMsgHandler->onPlayername = [this](const Playername& playerName) { OnMsgPlayerName(playerName); };
	m_pMsgHandler->onChatMessage = [this](const ChatMessage& cm) { OnChatMessage(cm); };
	m_pMsgHandler->onHandleGameSettings = [this](const HandleGameSettings& gs) { OnMsgHandleGameSettings(gs); };
	m_pMsgHandler->onGameState = [this](const GameState& gs) { OnGameState(gs); };
	m_pMsgHandler->onPlayerAnswers = [this](const PlayerAnswers& ans) { OnPlayerAnswers(ans); };
}

ServerInteractorImpl::~ServerInteractorImpl()
{}

void ServerInteractorImpl::StartServer()
{
	m_GameStats.lobbyCode = m_pServer->StartServer();
}

void ServerInteractorImpl::OnNewConnection(int id)
{
	PlayerID ID{id};
	auto serID = m_pSerializer->Serialize(ID);
	m_pServer->WriteTo(serID, id);

	//onLog("ServerInteractor: New Connection Handled; ID: " + std::to_string(id));
}

void ServerInteractorImpl::OnData(const ByteStream& stream, int id)
{
	auto des = m_pSerializer->Deserialize(stream);
	m_actualID = id; //how to pass through the id to the event funcs
	m_pMsgHandler->handleMessage(des);

	//onLog("ServerInteractor: received data: " + text + " from client: " + std::to_string(id));
}

void ServerInteractorImpl::OnLog(const std::string& text)
{
	//if(onLog)
	//	onLog("Server: " + text);
}

void ServerInteractorImpl::OnDisconnect(int id)
{
	m_GameStats.players.erase(id);

	auto stats = CreateHandleGameSettings();

	auto ser = m_pSerializer->Serialize(stats);
	m_pServer->Broadcast(ser);
}

void ServerInteractorImpl::OnMsgPlayerName(const Playername& playerName)
{
	m_GameStats.players.emplace(m_GameStats.players.size(), PlayerStats{ playerName.playername, 0, {} });

	auto stats = CreateHandleGameSettings();

	auto ser = m_pSerializer->Serialize(stats);
	m_pServer->Broadcast(ser);

	//for schleife -> WriteTo (neue id)
}

void ServerInteractorImpl::OnMsgHandleGameSettings(const HandleGameSettings& settings)
{
	m_GameStats.customCategoryString = settings.ls.categories;
	m_GameStats.timeout = settings.ls.timeout ;
	m_GameStats.maxRounds = std::stoi(settings.ls.rounds);

	auto msg = CreateHandleGameSettings();

	auto ser = m_pSerializer->Serialize(msg);
	m_pServer->Broadcast(ser);
}

void ServerInteractorImpl::OnChatMessage(const ChatMessage& cm)
{
	auto ser = m_pSerializer->Serialize(cm);
	m_pServer->Broadcast(ser);
}

void CheckAllAnswersRecived(int counter, int actualCount, Event<> onTrue)
{
	if (counter == actualCount)
	{
		onTrue();
	}
}

void ServerInteractorImpl::OnPlayerAnswers(const PlayerAnswers& answers)
{
	m_GameStats.players[m_actualID].answers = answers.answers;
	m_dataGatherCounter++;

	auto broadcast = [this]()
	{		
		AllAnswers allAnsw{};

		for (const auto& player : m_GameStats.players)
			allAnsw.ans.push_back(player.second.answers);

		auto ser = m_pSerializer->Serialize(allAnsw);
		m_pServer->Broadcast(ser);
	};

	CheckAllAnswersRecived(m_dataGatherCounter, m_GameStats.players.size(), broadcast);
}

void ServerInteractorImpl::OnGameState(const GameState& gs)
{
	m_GameStats.state = gs.state;
	HandleGameState(gs);
}

HandleGameSettings ServerInteractorImpl::CreateHandleGameSettings()
{
	HandleGameSettings result{};
	result.ls.categories = m_GameStats.customCategoryString;
	result.ls.rounds = std::to_string(m_GameStats.maxRounds);
	result.ls.timeout = m_GameStats.timeout;
	for (const auto& player : m_GameStats.players)
		result.ls.playerNames.emplace(player.first, player.second.playerName);
	return result;
}

void ServerInteractorImpl::HandleGameState(const GameState& gs)
{
	if (gs.state == STATE::ANSWERREQUEST)
	{
		auto ser = m_pSerializer->Serialize(gs);
		m_pServer->Broadcast(ser);
	}
	else if (gs.state == STATE::SETUPROUND)
	{
		m_pDataOperation->InkrementRound(m_GameStats);
		m_pDataOperation->AddPreviousLetter(m_GameStats);
		m_pDataOperation->SetNewLetter(m_pRandomGenerator->GenerateUnusedLetter(m_GameStats.lettersUsed), m_GameStats);
		m_GameStats.categories = m_pParser->ParseCategories(m_GameStats.customCategoryString);

		RoundSetup msg;
		msg.data.categories = m_GameStats.categories;
		msg.data.currentRound = m_GameStats.currentRound;
		msg.data.letter = m_GameStats.currentLetter;
		msg.data.maxRounds = m_GameStats.maxRounds;
		msg.data.roundTime = m_GameStats.timeout;
		for (const auto& player : m_GameStats.players)
		{
			msg.data.points = player.second.points;
			auto ser = m_pSerializer->Serialize(msg);
			m_pServer->WriteTo(ser, player.first);
		}
		//m_pServer->WriteTo();
	}
}
