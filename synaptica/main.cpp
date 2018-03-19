#include <QGuiApplication>
#include <QClipboard>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <qqmlcontext.h>
#include <QDebug>
#include <QObject>
#include "clipboardManage.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    ClipboardManage *clipboardInstance = new ClipboardManage();

    QQmlApplicationEngine engine;
    QQmlContext *ctx = engine.rootContext();
    ctx->setContextProperty("clipboardManage", clipboardInstance);

//    qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
//    qDebug() << QApplication::clipboard()->text();
//    qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
