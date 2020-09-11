#include "registertypes.h"

#include <QQmlEngine>

#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)

Logger *logger = nullptr;
Finger *fingerObj = nullptr;
AppState *appState = nullptr;
FingerboardCppInterface *fingerboardCppInterface = nullptr;

static QObject *fingerObjSingletonProvider(QQmlEngine *e, QJSEngine *j) {
  Q_UNUSED(j)

  if (fingerObj == nullptr) {
    fingerObj = new Finger(e);
  }

  return fingerObj;
}
static QObject *appStateSingletonProvider(QQmlEngine *e, QJSEngine *j) {
  Q_UNUSED(j)

  if (appState == nullptr) {
    appState = new AppState(e);
  }

  return appState;
}
static QObject *fingerboardCppInterfaceSingletonProvider(QQmlEngine *e,
                                                         QJSEngine *j) {
  Q_UNUSED(j)

  if (logger == nullptr) {
    logger = new Logger(e);
  }

  if (fingerObj == nullptr) {
    fingerObj = new Finger(e);
  }

  if (appState == nullptr) {
    appState = new AppState(e);
  }

  if (fingerboardCppInterface == nullptr) {
    fingerboardCppInterface =
        new FingerboardCppInterface(fingerObj, logger, appState, e);
  }

  return fingerboardCppInterface;
}

void registerQmlTypes(QObject *parent) {
  qmlRegisterSingletonType<FingerboardCppInterface>(
      "Fingerboard", 1, 0, "FingerboardCppInterface",
      fingerboardCppInterfaceSingletonProvider);

  qmlRegisterSingletonType<AppState>("Fingerboard", 1, 0, "AppState",
                                     appStateSingletonProvider);

  qmlRegisterSingletonType<Finger>("Fingerboard", 1, 0, "Finger",
                                   fingerObjSingletonProvider);
  qmlRegisterUncreatableType<Logger>(
      "Fingerboard", 1, 0, "Logger",
      "Logger can be instantiated from c++ only");
}
#else
void registerQmlTypes(QObject *parent) {
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
#endif
