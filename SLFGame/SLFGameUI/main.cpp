#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "QmlAdapter.h"
#include "controller.h"
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

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QmlAdapter qmlAdapter;
    RandomGenerator rndGen{};
    GameStatsOperations gsOperations{};
    Server server;
    GameStatsSerializer serializer;
    MessageHandler clientMsgHandler;
    MessageHandler serverMsgHandler;
    Game game;
    Client client;
    ServerInteractorImpl serverInteractor(&server, &serializer, &serverMsgHandler);
    ClientInteractorImpl clientInteractor(&client, &serializer, &clientMsgHandler);
    GameInteractorImpl gameInteractor(&game, &rndGen, &gsOperations, &serverInteractor);
    Controller controller{&qmlAdapter, &gameInteractor, &clientInteractor, &serverInteractor};
    return controller.Run(argc, argv, qmlAdapter);
}
