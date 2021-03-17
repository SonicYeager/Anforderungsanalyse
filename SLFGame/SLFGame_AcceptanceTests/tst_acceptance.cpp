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

private:
    void Cleanup();

    QmlAdapter qmlAdapter;
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
    GameInteractorImpl gameInteractor{&game, &rndGen, &gsOperations, &clientInteractor, &serverInteractor};
    Controller controller{&qmlAdapter, &gameInteractor};
};



Acceptance::Acceptance()
{}

Acceptance::~Acceptance()
{}

//void Acceptance::initTestCase()
//{}
//
//void Acceptance::cleanupTestCase()
//{}

void Acceptance::hostLobby_Jerk_ConnectionEstablishedGameStatsSet()
{
    qmlAdapter.setPlayerName("Jerk");

    qmlAdapter.hostLobby();
    QTest::qWait(50);

    QCOMPARE(gameInteractor.m_GameStats.players.size(), 1);
    QCOMPARE(gameInteractor.m_GameStats.players[0].playerName, "Jerk");

    Cleanup();
}

void Acceptance::lobbySettingsChanged_ChangedTimeLeft_SettingsWithStandardCatAndRounds()
{
    qmlAdapter.setPlayerName("Jerk");
    qmlAdapter.setRoundTime("00:01:10");
    qmlAdapter.setCustomCategories("Stabby");
    qmlAdapter.setMaxRounds("100");

    qmlAdapter.joinLobby();
    QTest::qWait(50);
    qmlAdapter.lobbySettingsChanged();
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
    qmlAdapter.setPlayerName("Jerk");

    qmlAdapter.joinLobby();
    QTest::qWait(50);
    qmlAdapter.onChatMessage("Sender", "Message");
    QTest::qWait(50);

    auto actual = qmlAdapter.getChatLog();
    QString expected = "Sender: Message\n";
    QCOMPARE(actual, expected);

    Cleanup();
}

void Acceptance::onePlayerAnswer_playerAnswer_playerAnswersSavedOnGameStats()
{
    qmlAdapter.setPlayerName("Jerk");

    qmlAdapter.joinLobby();
    QTest::qWait(50);
    qmlAdapter.onSendAnswers({"Le","Mans","66"});
    QTest::qWait(50);

    auto id = qmlAdapter.getPlayerId();
    auto actual = gameInteractor.m_GameStats.players[id].answers;
    std::vector<std::string> expected = {"Le","Mans","66"};
    QVERIFY(actual == expected);

    Cleanup();
}

void Acceptance::stateChanged_stateLobby_stateChangedInGameStats()
{
    qmlAdapter.setPlayerName("Jerk");

    qmlAdapter.joinLobby();
    QTest::qWait(50);
    qmlAdapter.onState(STATE::LOBBY);
    QTest::qWait(50);

    auto actual = gameInteractor.m_GameStats.state;
    auto expected = STATE::LOBBY;
    QVERIFY(actual == expected);

    Cleanup();
}

void Acceptance::Cleanup()
{
    client.DisconnectFromServer();
}

QTEST_GUILESS_MAIN(Acceptance)

#include "tst_acceptance.moc"