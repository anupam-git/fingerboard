#ifndef INTERFACES_FINGERBOARD_CPP_INTERFACE
#define INTERFACES_FINGERBOARD_CPP_INTERFACE

#include <QDBusInterface>
#include <QObject>

#include "fprintddeviceinterface.h"
#include "fprintdmanagerinterface.h"
#include "utils/logger.h"

#define FPRINTD_SERVICE "net.reactivated.Fprint"

class FingerboardCppInterface : public QObject {
  Q_OBJECT

 public:
  FingerboardCppInterface(QObject *parent = nullptr);
  Logger *logger;

 public slots:
  void init();
  void deviceInfo();
  void listFp();
  void enrollFp();
  void verifyFp();
  void deleteFp();

 signals:
  void log(QString msg);
  void operationComplete();

 private:
  net::reactivated::Fprint::Device *fprintdInterfaceDevice;
  net::reactivated::Fprint::Manager *fprintdInterfaceManager;
  QDBusInterface *fprintdDevicePropertiesInterface;
  QString username = qgetenv("USER");

  void claimFpDevice();
  void releaseFpDevice();
};

#endif  // INTERFACES_FINGERBOARD_CPP_INTERFACE
