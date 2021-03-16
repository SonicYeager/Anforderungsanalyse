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
    QCOMPARE(qmlAdapter.getPlayerName(), "Jerk");
    QCOMPARE(qmlAdapter.getPlayerId(), 0);
    QCOMPARE(qmlAdapter.getLobbyCode(), "192.168.0.80");

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

void Acceptance::Cleanup()
{
    client.DisconnectFromServer();
}

QTEST_GUILESS_MAIN(Acceptance)

#include "tst_acceptance.moc"
