#ifndef INTERFACES_FINGERBOARD_CPP_INTERFACE_H
#define INTERFACES_FINGERBOARD_CPP_INTERFACE_H

#include <QDBusInterface>
#include <QObject>

#include "fprintddeviceinterface.h"
#include "fprintdmanagerinterface.h"
#include "utils/appstate.h"
#include "utils/deviceinfo.h"
#include "utils/finger.h"
#include "utils/logger.h"

#define FPRINTD_SERVICE "net.reactivated.Fprint"

class FingerboardCppInterface : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString deviceName READ getDeviceName NOTIFY deviceNameChanged)
  Q_PROPERTY(QString scanType READ getScanType NOTIFY scanTypeChanged)
  Q_PROPERTY(
      int numEnrollStages READ getNumEnrollStages NOTIFY numEnrollStagesChanged)

 public:
  FingerboardCppInterface(Finger *fingerObj, Logger *logger, AppState *appState,
                          QObject *parent = nullptr);

  QString getDeviceName();
  QString getScanType();
  int getNumEnrollStages();

 public slots:
  void init();
  void deviceInfo();
  void listFp();
  bool enrollFp(int finger);
  bool verifyFp(QString finger = "any");
  void deleteFp();

 signals:
  void enrolledFingerprintsList(QList<int> fingerprints);
  void log(int logLevel, QString msg);

  void deviceNameChanged(QString deviceName);
  void scanTypeChanged(QString scanType);
  void numEnrollStagesChanged(int numEnrollStages);

 private:
  net::reactivated::Fprint::Device *fprintdInterfaceDevice;
  net::reactivated::Fprint::Manager *fprintdInterfaceManager;
  QDBusInterface *fprintdDevicePropertiesInterface;
  QString username = qgetenv("USER");
  QString defaultDevicePath;
  AppState *appState;
  Logger *logger;
  Finger *fingerObj;

  QString _deviceName;
  QString _scanType;
  int _numEnrollStages;

  bool claimFpDevice();
  void releaseFpDevice();

 private slots:
  void enrollStatusSlot(QString result, bool done);
  void verifyStatusSlot(QString result, bool done);
};

#endif  // INTERFACES_FINGERBOARD_CPP_INTERFACE_H
