#include "fingerboard_cpp_interface.h"

#include <QDataStream>
#include <QString>

FingerboardCppInterface::FingerboardCppInterface(Finger *fingerObj,
                                                 Logger *logger,
                                                 AppState *appState,
                                                 QObject *parent)
    : QObject(parent) {
  this->fingerObj = fingerObj;
  this->appState = appState;
  this->logger = logger;

  connect(logger, &Logger::writeLog, [=](Logger::Level logLevel, QString msg) {
    emit log(logLevel, msg);
  });
}

QString FingerboardCppInterface::getDeviceName() { return _deviceName; }

QString FingerboardCppInterface::getScanType() { return _scanType; }

int FingerboardCppInterface::getNumEnrollStages() { return _numEnrollStages; }

void FingerboardCppInterface::init() {
  logger->log(Logger::INFO, QString("Log Location : %1").arg(logger->path()));
  logger->log(Logger::INFO, "Initializing Fingerboard");

  QDBusConnection bus = QDBusConnection::systemBus();
  fprintdInterfaceManager = new net::reactivated::Fprint::Manager(
      QString(FPRINTD_SERVICE), QString("/net/reactivated/Fprint/Manager"), bus,
      this);

  QDBusPendingReply<QDBusObjectPath> defaultDevicePathReply =
      fprintdInterfaceManager->GetDefaultDevice();
  defaultDevicePathReply.waitForFinished();
  defaultDevicePath = defaultDevicePathReply.value().path();

  if (defaultDevicePath.size() > 0) {
    logger->log(
        Logger::DEBUG,
        QString("Default Device Object Path : %1").arg(defaultDevicePath));

    fprintdInterfaceDevice = new net::reactivated::Fprint::Device(
        QString(FPRINTD_SERVICE), defaultDevicePath, bus, this);
    fprintdDevicePropertiesInterface = new QDBusInterface(
        QString(FPRINTD_SERVICE), defaultDevicePath,
        QString("org.freedesktop.DBus.Properties"), bus, this);

    connect(fprintdInterfaceDevice, SIGNAL(EnrollStatus(QString, bool)), this,
            SLOT(enrollStatusSlot(QString, bool)));
    connect(fprintdInterfaceDevice, SIGNAL(VerifyStatus(QString, bool)), this,
            SLOT(verifyStatusSlot(QString, bool)));

    deviceInfo();
    listFp();
  } else {
    logger->log(Logger::ERROR, appState->errorStatusString(
                                   AppState::ErrorStatus::ERROR_NO_DEVICE));
    appState->raiseError(AppState::ErrorStatus::ERROR_NO_DEVICE);
  }
}

void FingerboardCppInterface::deviceInfo() {
  if (claimFpDevice()) {
    _deviceName = fprintdDevicePropertiesInterface->call("Get", "", "name")
                      .arguments()
                      .at(0)
                      .value<QDBusVariant>()
                      .variant()
                      .toString();
    _scanType = fprintdDevicePropertiesInterface->call("Get", "", "scan-type")
                    .arguments()
                    .at(0)
                    .value<QDBusVariant>()
                    .variant()
                    .toString();
    _numEnrollStages =
        fprintdDevicePropertiesInterface->call("Get", "", "num-enroll-stages")
            .arguments()
            .at(0)
            .value<QDBusVariant>()
            .variant()
            .toInt();

    emit deviceNameChanged(_deviceName);
    emit scanTypeChanged(_scanType);
    emit numEnrollStagesChanged(_numEnrollStages);

    logger->log(Logger::INFO, QString("-----------"));
    logger->log(Logger::INFO, QString("Device Info"));
    logger->log(Logger::INFO, QString("-----------"));
    logger->log(Logger::INFO,
                QString("    Name          : %1").arg(_deviceName));
    logger->log(Logger::INFO, QString("    Scan Type     : %1").arg(_scanType));
    logger->log(Logger::INFO,
                QString("    Enroll Stages : %1").arg(_numEnrollStages));

    releaseFpDevice();
  }
}

void FingerboardCppInterface::listFp() {
  if (claimFpDevice()) {
    logger->log(Logger::VERBOSE, "Start Listing FP");
    logger->log(Logger::INFO, "Listing Fingerprints");

    emit appState->listingStarted();

    QDBusPendingReply<QStringList> listEnrolledFingersReply =
        fprintdInterfaceDevice->ListEnrolledFingers(username);
    listEnrolledFingersReply.waitForFinished();

    if (listEnrolledFingersReply.error().isValid()) {
      logger->log(Logger::ERROR,
                  QString("%1 : %2")
                      .arg(listEnrolledFingersReply.error().name())
                      .arg(listEnrolledFingersReply.error().message()));

      if (appState->errorStatusFromRawString(
              listEnrolledFingersReply.error().name()) ==
          AppState::ErrorStatus::ERROR_NO_ENROLLED_PRINTS) {
        emit enrolledFingerprintsList(QList<int>());
      } else {
        appState->raiseError(listEnrolledFingersReply.error().name());
      }
    } else {
      QStringList rawEnrolledFingersList = listEnrolledFingersReply.value();
      QList<int> enrolledFingers;

      logger->log(Logger::DEBUG, "ENROLLED FINGERPRINTS");
      for (QString finger : rawEnrolledFingersList) {
        logger->log(Logger::DEBUG, QString("  - %1").arg(finger));
        enrolledFingers.append(fingerObj->fromName(finger));
      }

      emit enrolledFingerprintsList(enrolledFingers);
    }

    logger->log(Logger::VERBOSE, "End Listing FP");
    releaseFpDevice();

    emit appState->listingCompleted();
  }
}

void FingerboardCppInterface::enrollFp(int finger) {
  if (claimFpDevice()) {
    logger->log(Logger::VERBOSE,
                QString("Start Enrolling FP : [%1]").arg(finger));
    logger->log(Logger::INFO, "Starting Enrolling Fingerprint");

    QDBusPendingReply enrollStartReply =
        fprintdInterfaceDevice->EnrollStart(fingerObj->rawFingerName(finger));
    enrollStartReply.waitForFinished();

    if (enrollStartReply.error().isValid()) {
      logger->log(Logger::ERROR, QString("%1 : %2")
                                     .arg(enrollStartReply.error().name())
                                     .arg(enrollStartReply.error().message()));

      appState->raiseError(enrollStartReply.error().name());
      logger->log(Logger::VERBOSE, "End Enrolling FP");
      releaseFpDevice();
    } else {
      logger->log(Logger::VERBOSE, "Touch/Swipe to start Enrolling");
      appState->setEnrollStatus(AppState::ENROLL_START);

      emit appState->enrollStarted();
    }
  }
}

void FingerboardCppInterface::verifyFp(QString finger) {
  if (claimFpDevice()) {
    logger->log(Logger::VERBOSE,
                QString("Start Verifying FP : [%1]").arg(finger));
    logger->log(Logger::INFO, "Starting Verifying Fingerprint");

    QDBusPendingReply verifyStartReply =
        fprintdInterfaceDevice->VerifyStart(finger);
    verifyStartReply.waitForFinished();

    if (verifyStartReply.error().isValid()) {
      logger->log(Logger::ERROR, QString("%1 : %2")
                                     .arg(verifyStartReply.error().name())
                                     .arg(verifyStartReply.error().message()));

      appState->raiseError(verifyStartReply.error().name());
      logger->log(Logger::VERBOSE, "End Verifying FP");
      releaseFpDevice();
    } else {
      logger->log(Logger::VERBOSE, "Touch/Swipe to continue Verifying");
      appState->setVerifyStatus(AppState::VERIFY_START);

      emit appState->verifyStarted();
    }
  }
}

void FingerboardCppInterface::deleteFp() {
  if (claimFpDevice()) {
    logger->log(Logger::VERBOSE, "Start Deleting FP");
    logger->log(Logger::INFO, "Deleting Fingerprints");

    emit appState->deleteStarted();

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
      appState->raiseError(deleteEnrolledFingers2Reply.error().name());
    }

    logger->log(Logger::VERBOSE, "End Deleting FP");
    releaseFpDevice();

    emit appState->deleteCompleted();
  }
}

void FingerboardCppInterface::enrollStatusSlot(QString result, bool done) {
  logger->log(
      Logger::DEBUG,
      QString("ENROLL STATUS : %1, ENROLL DONE : %2").arg(result).arg(done));

  appState->setEnrollStatus(appState->enrollStatusFromRawString(result));

  if (result == "enroll-completed" || result == "enroll-failed" ||
      result == "enroll-data-full" || result == "enroll-unknown-error" ||
      done) {
    QDBusPendingReply enrollStopReply = fprintdInterfaceDevice->EnrollStop();
    enrollStopReply.waitForFinished();
    logger->log(Logger::INFO,
                QString("Enroll Ended with status [%1]").arg(result));
    logger->log(Logger::VERBOSE, "End Enrolling FP");
    releaseFpDevice();

    if (result == "enroll-completed") {
      emit appState->enrollCompleted();
    } else {
      emit appState->enrollErrored();
    }
  }
}

void FingerboardCppInterface::verifyStatusSlot(QString result, bool done) {
  logger->log(
      Logger::DEBUG,
      QString("VERIFY STATUS : %1, VERIFY DONE : %2").arg(result).arg(done));

  appState->setVerifyStatus(appState->verifyStatusFromRawString(result));

  if (result == "verify-no-match" || result == "verify-match" ||
      result == "verify-unknown-error" || done) {
    QDBusPendingReply verifyStopReply = fprintdInterfaceDevice->VerifyStop();
    verifyStopReply.waitForFinished();
    logger->log(Logger::INFO,
                QString("Verify Ended with status [%1]").arg(result));
    logger->log(Logger::VERBOSE, "End Verifying FP");
    releaseFpDevice();

    if (result == "verify-match") {
      emit appState->verifyCompleted();
    } else {
      emit appState->verifyErrored();
    }
  }
}

bool FingerboardCppInterface::claimFpDevice() {
  logger->log(Logger::DEBUG, "Claiming Fingerprint Device");

  if (defaultDevicePath.size() <= 0) {
    logger->log(Logger::ERROR, appState->errorStatusString(
                                   AppState::ErrorStatus::ERROR_NO_DEVICE));
    appState->raiseError(AppState::ErrorStatus::ERROR_NO_DEVICE);

    return false;
  } else {
    QDBusPendingReply claimReply = fprintdInterfaceDevice->Claim(QString());
    claimReply.waitForFinished();

    if (claimReply.error().isValid()) {
      logger->log(Logger::ERROR, QString("%1 : %2")
                                     .arg(claimReply.error().name())
                                     .arg(claimReply.error().message()));

      appState->raiseError(claimReply.error().name());
      return false;
    }
  }

  return true;
}

void FingerboardCppInterface::releaseFpDevice() {
  logger->log(Logger::DEBUG, "Releasing Fingerprint Device");

  QDBusPendingReply releaseReply = fprintdInterfaceDevice->Release();

  if (releaseReply.error().isValid()) {
    logger->log(Logger::ERROR, QString("%1 : %2")
                                   .arg(releaseReply.error().name())
                                   .arg(releaseReply.error().message()));

    appState->raiseError(releaseReply.error().name());
  }
}
