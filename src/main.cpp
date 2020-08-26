#include "interfaces/fingerboard_cpp_interface.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

void registerQmlTypes(QObject *parent = nullptr) {
  FingerboardCppInterface *fingerboardCppInterface =
      new FingerboardCppInterface(parent);

  qmlRegisterSingletonInstance<FingerboardCppInterface>(
      "Fingerboard", 1, 0, "FingerboardCppInterface", fingerboardCppInterface);
}

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  registerQmlTypes(&app);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
