#ifndef UTILS_APPSTATE_H
#define UTILS_APPSTATE_H

#include <QMap>
#include <QObject>
#include <QSet>
#include <QString>

class AppState : public QObject {
  Q_OBJECT

 public:
  enum ErrorStatus {
    ERROR_NO_DEVICE,

    ERROR_PERMISSION_DENIED,
    ERROR_NO_ENROLLED_PRINTS,
    ERROR_ALREADY_IN_USE,
    ERROR_INTERNAL,
    ERROR_CLAIM_DEVICE,
    ERROR_NO_ACTION_IN_PROGRESS,
    ERROR_INVALID_FINGERNAME,
  };
  Q_ENUM(ErrorStatus);

  enum EnrollStatus {
    ENROLL_COMPLETED,
    ENROLL_FAILED,
    ENROLL_STAGE_PASSED,
    ENROLL_RETRY_SCAN,
    ENROLL_SWIPE_TOO_SHORT,
    ENROLL_FINGER_NOT_CENTERED,
    ENROLL_REMOVE_AND_RETRY,
    ENROLL_DATA_FULL,
    ENROLL_DISCONNECTED,
    ENROLL_UNKNOWN_ERROR
  };
  Q_ENUM(EnrollStatus)

  enum VerifyStatus {
    VERIFY_NO_MATCH,
    VERIFY_MATCH,
    VERIFY_RETRY_SCAN,
    VERIFY_SWIPE_TOO_SHORT,
    VERIFY_FINGER_NOT_CENTERED,
    VERIFY_REMOVE_AND_RETRY,
    VERIFY_DISCONNECTED,
    VERIFY_UNKNOWN_ERROR
  };
  Q_ENUM(VerifyStatus)

  enum Finger {
    FINGER_LEFT_THUMB,
    FINGER_LEFT_INDEX,
    FINGER_LEFT_MIDDLE,
    FINGER_LEFT_RING,
    FINGER_LEFT_LITTLE,
    FINGER_RIGHT_THUMB,
    FINGER_RIGHT_INDEX,
    FINGER_RIGHT_MIDDLE,
    FINGER_RIGHT_RING,
    FINGER_RIGHT_LITTLE
  };
  Q_ENUM(Finger)

  AppState(QObject *parent = nullptr);

  void raiseError(QString rawError);
  void raiseError(AppState::ErrorStatus errorStatus);

 public slots:
  QString errorStatusString(AppState::ErrorStatus status);
  QString enrollStatusString(AppState::EnrollStatus status);
  QString verifyStatusString(AppState::VerifyStatus status);
  QString fingerString(AppState::Finger finger);

 signals:
  void error(int errorStatus, QString errorString);

 private:
  QMap<QString, AppState::ErrorStatus> rawErrorMap = {
      {"net.reactivated.Fprint.Error.PermissionDenied",
       ErrorStatus::ERROR_PERMISSION_DENIED},
      {"net.reactivated.Fprint.Error.NoEnrolledPrints",
       ErrorStatus::ERROR_NO_ENROLLED_PRINTS},
      {"net.reactivated.Fprint.Error.AlreadyInUse",
       ErrorStatus::ERROR_ALREADY_IN_USE},
      {"net.reactivated.Fprint.Error.Internal", ErrorStatus::ERROR_INTERNAL},
      {"net.reactivated.Fprint.Error.ClaimDevice",
       ErrorStatus::ERROR_CLAIM_DEVICE},
      {"net.reactivated.Fprint.Error.NoActionInProgress",
       ErrorStatus::ERROR_NO_ACTION_IN_PROGRESS},
      {"net.reactivated.Fprint.Error.InvalidFingername",
       ErrorStatus::ERROR_INVALID_FINGERNAME}};
};

#endif  // UTILS_APPSTATE_H
