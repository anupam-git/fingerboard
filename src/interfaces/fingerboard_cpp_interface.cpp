#include "fingerboard_cpp_interface.h"

#include <QDataStream>
#include <QDebug>
#include <QString>

FingerboardCppInterface::FingerboardCppInterface(QObject* parent)
    : QObject(parent) {
  this->parent = parent;
  logger = new Logger(parent);
  connect(logger, &Logger::writeLog, [=](QString msg) { emit log(msg); });
}

void FingerboardCppInterface::init() {
  logger->log(Logger::INFO, "Initializing Fingerboard");

  QDBusConnection bus = QDBusConnection::systemBus();
  fprintdInterfaceManager = new net::reactivated::Fprint::Device(
      "/net/reactivated/Fprint/Manager", "net.reactivated.Fprint.Manager", bus);

  QString defaultDevicePath = fprintdInterfaceManager->call("GetDefaultDevice")
                                  .arguments()
                                  .at(0)
                                  .value<QDBusObjectPath>()
                                  .path();

  logger->log(
      Logger::DEBUG,
      QString("Default Device Object Path : %1").arg(defaultDevicePath));

  fprintdInterfaceDevice =
      new QDBusInterface("net.reactivated.Fprint", defaultDevicePath,
                         "net.reactivated.Fprint.Device", bus, parent);

  deviceInfo();
}

void FingerboardCppInterface::deviceInfo() {
  QString deviceName = fprintdInterfaceDevice->property("name").toString();
  QString scanType = fprintdInterfaceDevice->property("scan-type").toString();
  int enrollStages =
      fprintdInterfaceDevice->property("num-enroll-stages").toInt();

  logger->log(Logger::INFO, QString("-----------"));
  logger->log(Logger::INFO, QString("Device Info"));
  logger->log(Logger::INFO, QString("-----------"));
  logger->log(Logger::INFO, QString("    Name          : %1").arg(deviceName));
  logger->log(Logger::INFO, QString("    Scan Type     : %1").arg(scanType));
  logger->log(Logger::INFO,
              QString("    Enroll Stages : %1").arg(enrollStages));
}

void FingerboardCppInterface::listFp() {
  logger->log(Logger::DEBUG, "Start Listing FP");
  claimFpDevice();

  QDBusMessage responseMsg =
      fprintdInterfaceDevice->call("ListEnrolledFingers", username);
  qDebug() << "Listing Response :" << responseMsg;

  releaseFpDevice();
  logger->log(Logger::DEBUG, "End Listing FP");
}

void FingerboardCppInterface::enrollFp() {
  logger->log(Logger::DEBUG, "Start Enrolling FP");
  claimFpDevice();

  fprintdInterfaceDevice->call("EnrollStart", "right-index");

  releaseFpDevice();
  logger->log(Logger::DEBUG, "End Enrolling FP");
}

void FingerboardCppInterface::verifyFp() {
  logger->log(Logger::DEBUG, "Start Verifying FP");
  claimFpDevice();

  releaseFpDevice();
  logger->log(Logger::DEBUG, "End Verifying FP");
}

void FingerboardCppInterface::deleteFp() {
  logger->log(Logger::DEBUG, "Deleting FP");
  claimFpDevice();

  releaseFpDevice();
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
