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
  defaultDevicePath = defaultDevicePathReply.value().path();

  logger->log(
      Logger::DEBUG,
      QString("Default Device Object Path : %1").arg(defaultDevicePath));

  fprintdInterfaceDevice = new net::reactivated::Fprint::Device(
      QString(FPRINTD_SERVICE), defaultDevicePath, bus, this);
  fprintdDevicePropertiesInterface =
      new QDBusInterface(QString(FPRINTD_SERVICE), defaultDevicePath,
                         QString("org.freedesktop.DBus.Properties"), bus, this);

  connect(fprintdInterfaceDevice, SIGNAL(EnrollStatus(QString, bool)), this,
          SLOT(enrollStatusSlot(QString, bool)));
  connect(fprintdInterfaceDevice, SIGNAL(VerifyStatus(QString, bool)), this,
          SLOT(verifyStatusSlot(QString, bool)));

  deviceInfo();
}

void FingerboardCppInterface::deviceInfo() {
  if (claimFpDevice()) {
    QString deviceName =
        fprintdDevicePropertiesInterface->call("Get", "", "name")
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
    logger->log(Logger::INFO,
                QString("    Name          : %1").arg(deviceName));
    logger->log(Logger::INFO, QString("    Scan Type     : %1").arg(scanType));
    logger->log(Logger::INFO,
                QString("    Enroll Stages : %1").arg(enrollStages));

    releaseFpDevice();
    emit operationComplete();
  }
}

void FingerboardCppInterface::listFp() {
  if (claimFpDevice()) {
    logger->log(Logger::DEBUG, "Start Listing FP");

    QDBusPendingReply<QStringList> listEnrolledFingersReply =
        fprintdInterfaceDevice->ListEnrolledFingers(username);
    listEnrolledFingersReply.waitForFinished();

    if (listEnrolledFingersReply.error().isValid()) {
      logger->log(Logger::ERROR,
                  QString("ERROR[%1] : %2")
                      .arg(listEnrolledFingersReply.error().name())
                      .arg(listEnrolledFingersReply.error().message()));
    } else {
      QStringList enrolledFingersList = listEnrolledFingersReply.value();

      logger->log(Logger::VERBOSE, "ENROLLED FINGERPRINTS");
      for (QString finger : enrolledFingersList) {
        logger->log(Logger::VERBOSE, QString("  - %1").arg(finger));
      }
    }

    logger->log(Logger::DEBUG, "End Listing FP");
    releaseFpDevice();
    emit operationComplete();
  }
}

void FingerboardCppInterface::enrollFp(QString finger) {
  if (claimFpDevice()) {
    logger->log(Logger::DEBUG,
                QString("Start Enrolling FP : [%1]").arg(finger));

    QDBusPendingReply enrollStartReply =
        fprintdInterfaceDevice->EnrollStart(finger);
    enrollStartReply.waitForFinished();

    qDebug() << "Enroll Start Reply :" << enrollStartReply.reply();

    if (enrollStartReply.error().isValid()) {
      logger->log(Logger::ERROR, QString("%1 : %2")
                                     .arg(enrollStartReply.error().name())
                                     .arg(enrollStartReply.error().message()));

      logger->log(Logger::DEBUG, "End Enrolling FP");
      releaseFpDevice();
    } else {
      logger->log(Logger::VERBOSE, "Touch/Swipe to continue Enrolling");
    }
  }
}

void FingerboardCppInterface::verifyFp(QString finger) {
  if (claimFpDevice()) {
    logger->log(Logger::DEBUG,
                QString("Start Verifying FP : [%1]").arg(finger));

    QDBusPendingReply verifyStartReply =
        fprintdInterfaceDevice->VerifyStart(finger);
    verifyStartReply.waitForFinished();

    qDebug() << "Verify Start Reply :" << verifyStartReply.reply();

    if (verifyStartReply.error().isValid()) {
      logger->log(Logger::ERROR, QString("%1 : %2")
                                     .arg(verifyStartReply.error().name())
                                     .arg(verifyStartReply.error().message()));

      logger->log(Logger::DEBUG, "End Verifying FP");
      releaseFpDevice();
    } else {
      logger->log(Logger::VERBOSE, "Touch/Swipe to continue Verifying");
    }
  }
}

void FingerboardCppInterface::deleteFp() {
  if (claimFpDevice()) {
    logger->log(Logger::DEBUG, "Start Deleting FP");

    logger->log(
        Logger::INFO,
        QString("Deleting all fingerprints of user [%1] for device [%2]")
            .arg(username)
            .arg(defaultDevicePath));

    QDBusPendingReply deleteEnrolledFingers2Reply =
        fprintdInterfaceDevice->DeleteEnrolledFingers2();
    deleteEnrolledFingers2Reply.waitForFinished();

    if (deleteEnrolledFingers2Reply.error().isValid()) {
      logger->log(Logger::ERROR,
                  QString("%1 : %2")
                      .arg(deleteEnrolledFingers2Reply.error().name())
                      .arg(deleteEnrolledFingers2Reply.error().message()));
    }

    logger->log(Logger::DEBUG, "End Deleting FP");
    releaseFpDevice();
    emit operationComplete();
  }
}

void FingerboardCppInterface::enrollStatusSlot(QString result, bool done) {
  logger->log(
      Logger::DEBUG,
      QString("ENROLL STATUS : %1, ENROLL DONE : %2").arg(result).arg(done));

  if (result == "enroll-completed" || result == "enroll-failed" ||
      result == "enroll-data-full" || result == "enroll-unknown-error" ||
      done) {
    QDBusPendingReply enrollStopReply = fprintdInterfaceDevice->EnrollStop();
    enrollStopReply.waitForFinished();
    logger->log(Logger::INFO,
                QString("Enroll Ended with status [%1]").arg(result));
    logger->log(Logger::DEBUG, "End Enrolling FP");
    releaseFpDevice();
    emit operationComplete();
  }
}

void FingerboardCppInterface::verifyStatusSlot(QString result, bool done) {
  logger->log(
      Logger::DEBUG,
      QString("VERIFY STATUS : %1, VERIFY DONE : %2").arg(result).arg(done));

  if (result == "verify-no-match" || result == "verify-match" ||
      result == "verify-unknown-error" || done) {
    QDBusPendingReply verifyStopReply = fprintdInterfaceDevice->VerifyStop();
    verifyStopReply.waitForFinished();
    logger->log(Logger::INFO,
                QString("Verify Ended with status [%1]").arg(result));
    logger->log(Logger::DEBUG, "End Verifying FP");
    releaseFpDevice();
    emit operationComplete();
  }
}

bool FingerboardCppInterface::claimFpDevice() {
  logger->log(Logger::INFO, "Claiming Fingerprint Device");

  QDBusPendingReply claimReply = fprintdInterfaceDevice->Claim(QString());
  claimReply.waitForFinished();

  if (claimReply.error().isValid()) {
    logger->log(Logger::ERROR, QString("%1 : %2")
                                   .arg(claimReply.error().name())
                                   .arg(claimReply.error().message()));

    return false;
  }

  qDebug() << "Claim Response :" << claimReply.reply();

  return true;
}

void FingerboardCppInterface::releaseFpDevice() {
  logger->log(Logger::INFO, "Releasing Fingerprint Device");

  QDBusPendingReply releaseReply = fprintdInterfaceDevice->Release();

  if (releaseReply.error().isValid()) {
    logger->log(Logger::ERROR, QString("%1 : %2")
                                   .arg(releaseReply.error().name())
                                   .arg(releaseReply.error().message()));
  }

  qDebug() << "Release Response :" << releaseReply.reply();
}
