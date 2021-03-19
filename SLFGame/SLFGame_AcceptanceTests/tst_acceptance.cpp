#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "../SLFGameUI/QmlAdapter.h"
#include "../SLFGameUI/controller.h"
#include "GameStatsOperations.h"
#include "RandomGenerator.h"
#include "SLFParser.h"
#include "Game.h"
#include "Client.h"
#include "GameStatsSerializer.h"
#include "MessageHandler.h"
#include "ClientInteractorImpl.h"
#include "ServerInteractorImpl.h"
#include "GameInteractorImpl.h"
#include "Server.h"

inline bool operator==(const std::vector<std::string>& left, const std::vector<std::string>& right)
{
    if(left.size() != right.size())
        return false;
    for(int i{}; i < left.size(); ++i)
    {
        if(left[i] != right[i])
            return false;
    }
    return true;
}

class Acceptance : public QObject
{
    Q_OBJECT

public:
    Acceptance();
    ~Acceptance();

private slots:
    //void initTestCase();
    //void cleanupTestCase();
    void hostLobby_Jerk_ConnectionEstablishedGameStatsSet();
    void lobbySettingsChanged_ChangedTimeLeft_SettingsWithStandardCatAndRounds();
    void chatMsg_Message_ChatLogHoldsOneMessage();
    void onePlayerAnswer_playerAnswer_playerAnswersSavedOnGameStats();
    void stateChanged_stateLobby_stateChangedInGameStats();
    void secondInstance_comm_todo();

private:
    void Cleanup();

    RandomGenerator rndGen{};
    GameStatsOperations gsOperations{};
    Server server;
    GameStatsSerializer serializer;
    MessageHandler clientMsgHandler;
    MessageHandler serverMsgHandler;
    Game game;
    Client client;
    ServerInteractorImpl serverInteractor{&server, &serializer, &serverMsgHandler};
    ClientInteractorImpl clientInteractor{&client, &serializer, &clientMsgHandler};
    GameInteractorImpl gameInteractor{&game, &rndGen, &gsOperations, &serverInteractor};

    int resutltID{};
    LobbySettings resutltLS{};
    LobbyCode resutltLC{};
    STATE resultState{};
    ChatMessage resultChatMsg{};
    std::vector<std::vector<std::string>> resultanswers{};
    RoundData resultRD{};
    Index resultIndex{};
};

class Second : public QObject
{
    Q_OBJECT

public:
    Second();
    void Cleanup();

    RandomGenerator rndGen{};
    GameStatsOperations gsOperations{};
    Server server;
    GameStatsSerializer serializer;
    MessageHandler clientMsgHandler;
    MessageHandler serverMsgHandler;
    Game game;
    Client client;
    ServerInteractorImpl serverInteractor{&server, &serializer, &serverMsgHandler};
    ClientInteractorImpl clientInteractor{&client, &serializer, &clientMsgHandler};
    GameInteractorImpl gameInteractor{&game, &rndGen, &gsOperations, &serverInteractor};

    int resutltID{};
    LobbySettings resutltLS{};
    LobbyCode resutltLC{};
    STATE resultState{};
    ChatMessage resultChatMsg{};
    std::vector<std::vector<std::string>> resultanswers{};
    RoundData resultRD{};
    Index resultIndex{};
};



Acceptance::Acceptance()
{
    clientInteractor.onReceivedID            = [this](int id)
                                                {resutltID = id;};

    clientInteractor.onUpdateLobbySettings   = [this](LobbySettings ls)
                                               {resutltLS = ls;};

    clientInteractor.onSetLobbyCode          = [this](LobbyCode lobbyCode)
                                               {resutltLC = lobbyCode;};

    clientInteractor.onGameState             = [this](STATE state)
                                               {resultState = state;};

    clientInteractor.onChatMessage           = [this](ChatMessage cm)
                                               {resultChatMsg = cm;};

    clientInteractor.onAllAnswers            = [this](std::vector<std::vector<std::string>> answers)
                                               {resultanswers = answers;};

    clientInteractor.onRoundData             = [this](const RoundData& data)
                                               {resultRD = data;};

    clientInteractor.onVoteChange            = [this](const Index idx)
                                                {resultIndex = idx;};

    clientInteractor.onStartServer = [this] {	serverInteractor.StartServer(); };
}

Acceptance::~Acceptance()
{}

//void Acceptance::initTestCase()
//{}
//
//void Acceptance::cleanupTestCase()
//{}

void Acceptance::hostLobby_Jerk_ConnectionEstablishedGameStatsSet()
{
    clientInteractor.HostLobby("Jerk");
    QTest::qWait(50);

    QCOMPARE(gameInteractor.m_GameStats.players.size(), 1);
    QCOMPARE(gameInteractor.m_GameStats.players[0].playerName, "Jerk");

    Cleanup();
}

void Acceptance::lobbySettingsChanged_ChangedTimeLeft_SettingsWithStandardCatAndRounds()
{
    clientInteractor.JoinLobby("192.168.0.80", "Dork"); //consider finding it automatically
    QTest::qWait(50);
    clientInteractor.LobbyChanged("Stabby", "00:01:10", "100");
    QTest::qWait(50);

    std::string actual = gameInteractor.m_GameStats.timeout;
    std::string expected = "00:01:10";
    QCOMPARE(actual, expected);
    actual = gameInteractor.m_GameStats.customCategoryString;
    expected = "Stabby";
    QCOMPARE(actual, expected);
    actual = std::to_string(gameInteractor.m_GameStats.maxRounds);
    expected = "100";
    QCOMPARE(actual, expected);

    Cleanup();
}

void Acceptance::chatMsg_Message_ChatLogHoldsOneMessage()
{
    clientInteractor.JoinLobby("192.168.0.80", "Mark");
    QTest::qWait(50);
    clientInteractor.ChatMessageReceived("Sender", "Message");
    QTest::qWait(100);

    auto msg = resultChatMsg;
    QCOMPARE(msg.sender.c_str(), "Sender");
    QCOMPARE(msg.text.c_str(), "Message");

    Cleanup();
}

void Acceptance::onePlayerAnswer_playerAnswer_playerAnswersSavedOnGameStats()
{
    clientInteractor.JoinLobby("192.168.0.80", "Murk");
    QTest::qWait(50);
    clientInteractor.AnswersReceived({"Le","Mans","66", "Le","Mans","66"});
    QTest::qWait(100);

    std::vector<std::string> expected = {"Le","Mans","66", "Le","Mans","66"};
    QVERIFY(resultanswers[resutltID] == expected);

    Cleanup();
}

void Acceptance::stateChanged_stateLobby_stateChangedInGameStats()
{
    clientInteractor.JoinLobby("192.168.0.80", "Klark1");
    QTest::qWait(50);
    clientInteractor.StateChangeTriggered(STATE::LOBBY);
    QTest::qWait(100);

    auto actual = resultState;
    auto expected = STATE::LOBBY;
    QVERIFY(actual == expected);

    Cleanup();
}

void Acceptance::secondInstance_comm_todo()
{
    Second sec{};

    sec.clientInteractor.JoinLobby("192.168.0.80", "Klark2");
    QTest::qWait(100);

    QCOMPARE(gameInteractor.m_GameStats.players.size(), 2);
    QCOMPARE(gameInteractor.m_GameStats.players[resutltID].playerName, "Klark2");

    Cleanup();
}

void Acceptance::Cleanup()
{
    client.DisconnectFromServer();
    resutltID = {};
    resutltLS= {};
    resutltLC = {};
    resultState = {};
    resultChatMsg = {};
    resultanswers = {};
    resultRD = {};
    resultIndex = {};
}



Second::Second()
{
    clientInteractor.onReceivedID            = [this](int id)
                                                {resutltID = id;};

    clientInteractor.onUpdateLobbySettings   = [this](LobbySettings ls)
                                               {resutltLS = ls;};

    clientInteractor.onSetLobbyCode          = [this](LobbyCode lobbyCode)
                                               {resutltLC = lobbyCode;};

    clientInteractor.onGameState             = [this](STATE state)
                                               {resultState = state;};

    clientInteractor.onChatMessage           = [this](ChatMessage cm)
                                               {resultChatMsg = cm;};

    clientInteractor.onAllAnswers            = [this](std::vector<std::vector<std::string>> answers)
                                               {resultanswers = answers;};

    clientInteractor.onRoundData             = [this](const RoundData& data)
                                               {resultRD = data;};

    clientInteractor.onVoteChange            = [this](const Index idx)
                                                {resultIndex = idx;};

    clientInteractor.onStartServer = [this] {	serverInteractor.StartServer(); };
}

void Second::Cleanup()
{
    client.DisconnectFromServer();
    resutltID = {};
    resutltLS= {};
    resutltLC = {};
    resultState = {};
    resultChatMsg = {};
    resultanswers = {};
    resultRD = {};
    resultIndex = {};
}

QTEST_GUILESS_MAIN(Acceptance)

#include "tst_acceptance.moc"
