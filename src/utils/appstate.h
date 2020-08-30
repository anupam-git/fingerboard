#ifndef UTILS_APPSTATE_H
#define UTILS_APPSTATE_H

#include <QObject>
#include <QSet>
#include <QString>

class AppState : public QObject {
  Q_OBJECT

 public:
  enum class ErrorStatus {
    ERROR_NONE,

    ERROR_LIST_PERMISSION_DENIED,
    ERROR_LIST_NO_ENROLLED_PRINTS,

    ERROR_DELETE_PERMISSION_DENIED,

    ERROR_CLAIM_PERMISSION_DENIED,
    ERROR_CLAIM_ALREADY_IN_USE,
    ERROR_CLAIM_INTERNAL,

    ERROR_RELEASE_PERMISSION_DENIED,
    ERROR_RELEASE_CLAIM_DEVICE,

    ERROR_VERIFY_PERMISSION_DENIED,
    ERROR_VERIFY_CLAIM_DEVICE,
    ERROR_VERIFY_ALREADY_IN_USE,
    ERROR_VERIFY_NO_ENROLLED_PRINTS,
    ERROR_VERIFY_NO_ACTION_IN_PROGRESS,
    ERROR_VERIFY_INTERNAL,

    ERROR_ENROLL_PERMISSION_DENIED,
    ERROR_ENROLL_CLAIM_DEVICE,
    ERROR_ENROLL_ALREADY_IN_USE,
    ERROR_ENROLL_INVALID_FINGERNAME,
    ERROR_ENROLL_NO_ACTION_IN_PROGRESS,
    ERROR_ENROLL_INTERNAL
  };
  Q_ENUM(ErrorStatus);

  enum class EnrollStatus {
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

  enum class VerifyStatus {
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

  enum class Finger {
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

 public slots:
  QString errorStatusString(AppState::ErrorStatus status);
  QString enrollStatusString(AppState::EnrollStatus status);
  QString verifyStatusString(AppState::VerifyStatus status);
  QString fingerString(AppState::Finger finger);

 signals:

 private:
  AppState::ErrorStatus _errorStatus;
};

#endif  // UTILS_APPSTATE_H
