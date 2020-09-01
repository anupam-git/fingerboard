#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "interfaces/fingerboard_cpp_interface.h"
#include "utils/appstate.h"
#include "utils/finger.h"

void registerQmlTypes(QObject *parent = nullptr) {
  Finger *fingerObj = new Finger(parent);
  Logger *logger = new Logger(parent);
  AppState *appState = new AppState(parent);
  FingerboardCppInterface *fingerboardCppInterface =
      new FingerboardCppInterface(fingerObj, logger, appState, parent);

  qmlRegisterSingletonInstance<FingerboardCppInterface>(
      "Fingerboard", 1, 0, "FingerboardCppInterface", fingerboardCppInterface);
  qmlRegisterSingletonInstance<AppState>("Fingerboard", 1, 0, "AppState",
                                         appState);
  qmlRegisterSingletonInstance<Finger>("Fingerboard", 1, 0, "Finger",
                                       fingerObj);
  qmlRegisterUncreatableType<Logger>(
      "Fingerboard", 1, 0, "Logger",
      "Logger can be instantiated from c++ only");
}

int main(int argc, char *argv[]) {
  QQuickStyle::setStyle("Material");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));

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
