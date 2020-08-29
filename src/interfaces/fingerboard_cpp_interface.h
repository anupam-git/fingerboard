#ifndef INTERFACES_FINGERBOARD_CPP_INTERFACE_H
#define INTERFACES_FINGERBOARD_CPP_INTERFACE_H

#include <QDBusInterface>
#include <QObject>

#include "fprintddeviceinterface.h"
#include "fprintdmanagerinterface.h"
#include "utils/appstate.h"
#include "utils/logger.h"

#define FPRINTD_SERVICE "net.reactivated.Fprint"

class FingerboardCppInterface : public QObject {
  Q_OBJECT

 public:
  FingerboardCppInterface(AppState *appState, QObject *parent = nullptr);
  Logger *logger;

 public slots:
  void init();
  void deviceInfo();
  void listFp();
  void enrollFp(QString finger);
  void verifyFp(QString finger = "any");
  void deleteFp();

 signals:
  void log(int logLevel, QString msg);
  void operationComplete();

 private:
  net::reactivated::Fprint::Device *fprintdInterfaceDevice;
  net::reactivated::Fprint::Manager *fprintdInterfaceManager;
  QDBusInterface *fprintdDevicePropertiesInterface;
  QString username = qgetenv("USER");
  QString defaultDevicePath;
  AppState *appState;

  bool claimFpDevice();
  void releaseFpDevice();

 private slots:
  void enrollStatusSlot(QString result, bool done);
  void verifyStatusSlot(QString result, bool done);
};

#endif  // INTERFACES_FINGERBOARD_CPP_INTERFACE_H
