#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QSettings>
#include "stopwatch.h"
#include "countdown.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    app.setOrganizationName("BenQ");
    app.setOrganizationDomain("BenQ.com");
    app.setApplicationName("StopWatch-CountDown");
    app.setWindowIcon(QIcon(":/image/alarmClock.png"));

    QQmlApplicationEngine engine;
    QQmlContext* ctxt = engine.rootContext();

    qRegisterMetaTypeStreamOperators<QList<QString> >("QList<QString>");

    StopWatch stopWatch;
    qmlRegisterType<CountDown>("CountDown", 1, 0, "CountDown");
    ctxt->setContextProperty("StopWatch",QVariant::fromValue(&stopWatch));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    return app.exec();
}
