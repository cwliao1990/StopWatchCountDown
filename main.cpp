#include "countdown.h"
#include "stopwatch.h"
#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QApplication app(argc, argv);
  app.setOrganizationName("Demo");
  app.setOrganizationDomain("Demo.com");
  app.setApplicationName("StopWatch-CountDown");
  app.setWindowIcon(QIcon(":/image/alarmClock.png"));

  QQmlApplicationEngine engine;
  QQmlContext *ctxt = engine.rootContext();

  qRegisterMetaTypeStreamOperators<QList<QString>>("QList<QString>");

  StopWatch stopWatch;
  qmlRegisterType<CountDown>("CountDown", 1, 0, "CountDown");
  ctxt->setContextProperty("StopWatch", QVariant::fromValue(&stopWatch));

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  engine.load(url);

  return app.exec();
}
