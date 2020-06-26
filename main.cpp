#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "filemodel.hpp"
#include "scrapimage.hpp"
#include "filedownloader.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<FileModel>("FileModel", 1, 0, "FileModel");
    qmlRegisterType<ScrapImage>("ScrapImage", 1, 0, "ScrapImage");
    qDebug() << QDir::currentPath();
    QDir().mkdir(QDir::currentPath() + R"(/Library)");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
