#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QmlAdapter.h"
#include "controller.h"
#include "GameInteractor.h"
#include "GameStatsOperations.h"
#include "LetterGenerator.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif


    QmlAdapter qmlAdapter;
    GameStatsOperations gso{};
    LetterGenerator lg{};
    GameInteractor gi{&lg, &gso};
    Controller controller{&qmlAdapter, &gi};
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
