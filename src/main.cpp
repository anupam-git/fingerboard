#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "../fingerboard_version.h"
#include "registertypes.h"

int main(int argc, char *argv[]) {
  QQuickStyle::setStyle("Material");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));

  app.setApplicationName("fingerboard");
  app.setApplicationDisplayName("Fingerboard");
  app.setApplicationVersion(FINGERBOARD_VERSION_STRING);
  app.setWindowIcon(QIcon(":/sc-apps-fingerboard.svg"));

  registerQmlTypes(&app);

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
