#ifndef UTILS_APPSTATE_H
#define UTILS_APPSTATE_H

#include <QMap>
#include <QObject>
#include <QSet>
#include <QString>

class AppState : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      EnrollStatus enrollStatus READ getEnrollStatus NOTIFY enrollStatusChanged)
  Q_PROPERTY(QString enrollStatusString READ getEnrollStatusString NOTIFY
                 enrollStatusChanged)

  Q_PROPERTY(
      VerifyStatus verifyStatus READ getVerifyStatus NOTIFY verifyStatusChanged)
  Q_PROPERTY(QString verifyStatusString READ getVerifyStatusString NOTIFY
                 verifyStatusChanged)

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
    ENROLL_EMPTY,

    ENROLL_START,
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
    VERIFY_EMPTY,

    VERIFY_START,
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

  AppState(QObject *parent = nullptr);

  ErrorStatus errorStatusFromRawString(QString rawErrorString);
  void raiseError(QString rawError);
  void raiseError(AppState::ErrorStatus errorStatus);

  EnrollStatus getEnrollStatus();
  QString getEnrollStatusString();
  EnrollStatus enrollStatusFromRawString(QString rawStatus);
  void setEnrollStatus(EnrollStatus status);

  VerifyStatus getVerifyStatus();
  QString getVerifyStatusString();
  VerifyStatus verifyStatusFromRawString(QString rawStatus);
  void setVerifyStatus(VerifyStatus status);

  void resetApp();

 public slots:
  QString errorStatusString(AppState::ErrorStatus status);

 signals:
  void listingCompleted();

  void enrollStatusChanged(EnrollStatus status);
  void enrollCompleted();
  void enrollErrored();

  void verifyStatusChanged(VerifyStatus status);
  void verifyCompleted();
  void verifyErrored();

  void deleteCompleted();

  void error(ErrorStatus errorStatus, QString errorString);

  void reset();

 private:
  EnrollStatus _enrollStatus = EnrollStatus::ENROLL_EMPTY;
  VerifyStatus _verifyStatus = VerifyStatus::VERIFY_EMPTY;

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

  QMap<QString, AppState::EnrollStatus> rawEnrollStatusMap = {
      {"enroll-completed", AppState::EnrollStatus::ENROLL_COMPLETED},
      {"enroll-failed", AppState::EnrollStatus::ENROLL_FAILED},
      {"enroll-stage-passed", AppState::EnrollStatus::ENROLL_STAGE_PASSED},
      {"enroll-retry-scan", AppState::EnrollStatus::ENROLL_RETRY_SCAN},
      {"enroll-swipe-too-short",
       AppState::EnrollStatus::ENROLL_SWIPE_TOO_SHORT},
      {"enroll-finger-not-centered",
       AppState::EnrollStatus::ENROLL_FINGER_NOT_CENTERED},
      {"enroll-remove-and-retry",
       AppState::EnrollStatus::ENROLL_REMOVE_AND_RETRY},
      {"enroll-data-full", AppState::EnrollStatus::ENROLL_DATA_FULL},
      {"enroll-disconnected", AppState::EnrollStatus::ENROLL_DISCONNECTED},
      {"enroll-unknown-error", AppState::EnrollStatus::ENROLL_UNKNOWN_ERROR}};

  QMap<QString, AppState::VerifyStatus> rawVerifyStatusMap = {
      {"verify-no-match", AppState::VerifyStatus::VERIFY_NO_MATCH},
      {"verify-match", AppState::VerifyStatus::VERIFY_MATCH},
      {"verify-retry-scan", AppState::VerifyStatus::VERIFY_RETRY_SCAN},
      {"verify-swipe-too-short",
       AppState::VerifyStatus::VERIFY_SWIPE_TOO_SHORT},
      {"verify-finger-not-centered",
       AppState::VerifyStatus::VERIFY_FINGER_NOT_CENTERED},
      {"verify-remove-and-retry",
       AppState::VerifyStatus::VERIFY_REMOVE_AND_RETRY},
      {"verify-disconnected", AppState::VerifyStatus::VERIFY_DISCONNECTED},
      {"verify-unknown-error", AppState::VerifyStatus::VERIFY_UNKNOWN_ERROR}};
};

#endif  // UTILS_APPSTATE_H
