#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QmlAdapter.h"
#include "controller.h"
#include "GameInteractor.h"
#include "GameStatsOperations.h"
#include "RandomGenerator.h"
#include "GameNetwork.h"
#include "SLFParser.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QmlAdapter qmlAdapter;
    RandomGenerator rndGen{};
    GameStatsOperations gsOperations{};
    GameNetwork network;
    SLFParser parser;
    Game game;
    GameInteractor gameInteractor{&rndGen, &gsOperations, &game, &network, &parser};
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
