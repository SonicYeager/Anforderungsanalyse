#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QmlAdapter.h"
#include "controller.h"
#include "GameInteractor.h"
#include "GameStatsOperations.h"
#include "RandomGenerator.h"
#include "SLFParser.h"
#include "Game.h"
#include "Client.h"
#include "Host.h"
#include "Network.h"
#include "GameStatsSerializer.h"
#include "NetworkHandler.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QmlAdapter qmlAdapter;
    RandomGenerator rndGen{};
    GameStatsOperations gsOperations{};
    SLFParser parser;
    Network net;
    Client client(&net);
    Host host(&net);
    Game game;
    GameStatsSerializer serializer;
    NetworkHandler netHandler;

    GameInteractor gameInteractor{&rndGen, &gsOperations, &game, &parser, &client, &host, &serializer, &netHandler};
    Controller controller{&qmlAdapter, &gameInteractor};
    controller.Run();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("qmlAdapter", &qmlAdapter);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
                     [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
