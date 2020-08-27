#include "fingerboard_cpp_interface.h"

#include <QDataStream>
#include <QDebug>
#include <QString>

FingerboardCppInterface::FingerboardCppInterface(QObject* parent)
    : QObject(parent) {
  logger = new Logger(parent);
  connect(logger, &Logger::writeLog, [=](QString msg) { emit log(msg); });
}

void FingerboardCppInterface::init() {
  logger->log(Logger::INFO, "Initializing Fingerboard");

  QDBusConnection bus = QDBusConnection::systemBus();
  fprintdInterfaceManager = new net::reactivated::Fprint::Manager(
      QString(FPRINTD_SERVICE), QString("/net/reactivated/Fprint/Manager"), bus,
      this);

  QDBusPendingReply<QDBusObjectPath> defaultDevicePathReply =
      fprintdInterfaceManager->GetDefaultDevice();
  defaultDevicePathReply.waitForFinished();
  QString defaultDevicePath =
      defaultDevicePathReply.argumentAt(0).value<QDBusObjectPath>().path();

  logger->log(
      Logger::DEBUG,
      QString("Default Device Object Path : %1").arg(defaultDevicePath));

  fprintdInterfaceDevice = new net::reactivated::Fprint::Device(
      QString(FPRINTD_SERVICE), defaultDevicePath, bus, this);
  fprintdDevicePropertiesInterface =
      new QDBusInterface(QString(FPRINTD_SERVICE), defaultDevicePath,
                         QString("org.freedesktop.DBus.Properties"), bus, this);

  deviceInfo();
}

void FingerboardCppInterface::deviceInfo() {
  claimFpDevice();

  QString deviceName = fprintdDevicePropertiesInterface->call("Get", "", "name")
                           .arguments()
                           .at(0)
                           .value<QDBusVariant>()
                           .variant()
                           .toString();
  QString scanType =
      fprintdDevicePropertiesInterface->call("Get", "", "scan-type")
          .arguments()
          .at(0)
          .value<QDBusVariant>()
          .variant()
          .toString();
  int enrollStages =
      fprintdDevicePropertiesInterface->call("Get", "", "num-enroll-stages")
          .arguments()
          .at(0)
          .value<QDBusVariant>()
          .variant()
          .toInt();

  logger->log(Logger::INFO, QString("-----------"));
  logger->log(Logger::INFO, QString("Device Info"));
  logger->log(Logger::INFO, QString("-----------"));
  logger->log(Logger::INFO, QString("    Name          : %1").arg(deviceName));
  logger->log(Logger::INFO, QString("    Scan Type     : %1").arg(scanType));
  logger->log(Logger::INFO,
              QString("    Enroll Stages : %1").arg(enrollStages));

  releaseFpDevice();
  emit operationComplete();
}

void FingerboardCppInterface::listFp() {
  logger->log(Logger::DEBUG, "Start Listing FP");
  claimFpDevice();

  QStringList enrolledFingersList =
      fprintdInterfaceDevice->call("ListEnrolledFingers", username)
          .arguments()
          .at(0)
          .toStringList();

  logger->log(Logger::VERBOSE, "ENROLLED FINGERPRINTS");
  for (QString finger : enrolledFingersList) {
    logger->log(Logger::VERBOSE, QString("  - %1").arg(finger));
  }

  releaseFpDevice();
  logger->log(Logger::DEBUG, "End Listing FP");
  emit operationComplete();
}

void FingerboardCppInterface::enrollFp() {
  logger->log(Logger::DEBUG, "Start Enrolling FP");
  claimFpDevice();

  fprintdInterfaceDevice->call("EnrollStart", "right-index");

  releaseFpDevice();
  logger->log(Logger::DEBUG, "End Enrolling FP");
  emit operationComplete();
}

void FingerboardCppInterface::verifyFp() {
  logger->log(Logger::DEBUG, "Start Verifying FP");
  claimFpDevice();

  releaseFpDevice();
  logger->log(Logger::DEBUG, "End Verifying FP");
  emit operationComplete();
}

void FingerboardCppInterface::deleteFp() {
  logger->log(Logger::DEBUG, "Deleting FP");
  claimFpDevice();

  releaseFpDevice();
  emit operationComplete();
}

void FingerboardCppInterface::claimFpDevice() {
  logger->log(Logger::INFO, "Claiming Fingerprint Device");

  QDBusMessage responseMsg = fprintdInterfaceDevice->call("Claim", QString());
  qDebug() << "Claim Response :" << responseMsg;
}

void FingerboardCppInterface::releaseFpDevice() {
  logger->log(Logger::INFO, "Releasing Fingerprint Device");

  QDBusMessage responseMsg = fprintdInterfaceDevice->call("Release");
  qDebug() << "Release Response :" << responseMsg;
}
