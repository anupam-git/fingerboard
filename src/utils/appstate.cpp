#include "appstate.h"

AppState::AppState(QObject *parent) : QObject(parent) {}

AppState::ErrorStatus AppState::errorStatusFromRawString(
    QString rawErrorString) {
  return rawErrorMap[rawErrorString];
}

void AppState::raiseError(QString rawError) {
  raiseError(rawErrorMap[rawError]);
}

void AppState::raiseError(AppState::ErrorStatus errorStatus) {
  emit error(errorStatus, errorStatusString(errorStatus));
}

AppState::EnrollStatus AppState::getEnrollStatus() { return _enrollStatus; }

AppState::EnrollStatus AppState::enrollStatusFromRawString(QString rawStatus) {
  return rawEnrollStatusMap[rawStatus];
}

void AppState::setEnrollStatus(AppState::EnrollStatus status) {
  _enrollStatus = status;
  emit enrollStatusChanged(status);
}

AppState::VerifyStatus AppState::getVerifyStatus() { return _verifyStatus; }

AppState::VerifyStatus AppState::verifyStatusFromRawString(QString rawStatus) {
  return rawVerifyStatusMap[rawStatus];
}

void AppState::setVerifyStatus(AppState::VerifyStatus status) {
  _verifyStatus = status;
  emit verifyStatusChanged(status);
}

void AppState::resetApp() {
  _enrollStatus = EnrollStatus::ENROLL_EMPTY;
  _verifyStatus = VerifyStatus::VERIFY_EMPTY;

  emit enrollStatusChanged(_enrollStatus);
  emit verifyStatusChanged(_verifyStatus);
}

QString AppState::errorStatusString(AppState::ErrorStatus status) {
  switch (status) {
    case AppState::ErrorStatus::ERROR_NO_DEVICE:
      return "No Fingerprint Reader found";
    case AppState::ErrorStatus::ERROR_PERMISSION_DENIED:
      return "User lacks the appropriate PolicyKit authorization";
    case AppState::ErrorStatus::ERROR_NO_ENROLLED_PRINTS:
      return "User doesn't have any fingerprints enrolled";
    case AppState::ErrorStatus::ERROR_ALREADY_IN_USE:
      return "Device is already claimed";
    case AppState::ErrorStatus::ERROR_INTERNAL:
      return "Device couldn't be claimed";
    case AppState::ErrorStatus::ERROR_CLAIM_DEVICE:
      return "Device was not claimed";
    case AppState::ErrorStatus::ERROR_NO_ACTION_IN_PROGRESS:
      return "There are no ongoing verification";
    case AppState::ErrorStatus::ERROR_INVALID_FINGERNAME:
      return "Finger name passed is invalid";
  }

  return "";
}

QString AppState::getEnrollStatusString() {
  switch (_enrollStatus) {
    case AppState::EnrollStatus::ENROLL_EMPTY:
      return "";
    case AppState::EnrollStatus::ENROLL_START:
      return "Touch/Swipe to start Enrolling";
    case AppState::EnrollStatus::ENROLL_FAILED:
      return "The enrollment failed";
    case AppState::EnrollStatus::ENROLL_COMPLETED:
      return "The enrollment successfully completed";
    case AppState::EnrollStatus::ENROLL_DATA_FULL:
      return "No further prints can be enrolled on this device";
    case AppState::EnrollStatus::ENROLL_RETRY_SCAN:
      return "Retry scanning the finger";
    case AppState::EnrollStatus::ENROLL_DISCONNECTED:
      return "The device was disconnected during the enrollment";
    case AppState::EnrollStatus::ENROLL_STAGE_PASSED:
      return "Enrollment stage passed";
    case AppState::EnrollStatus::ENROLL_UNKNOWN_ERROR:
      return "An unknown error occurred";
    case AppState::EnrollStatus::ENROLL_SWIPE_TOO_SHORT:
      return "Swipe was too short";
    case AppState::EnrollStatus::ENROLL_REMOVE_AND_RETRY:
      return "Remove the finger from the reader and retry scanning";
    case AppState::EnrollStatus::ENROLL_FINGER_NOT_CENTERED:
      return "Finger was not centered on the reader";
  }

  return "";
}

QString AppState::getVerifyStatusString() {
  switch (_verifyStatus) {
    case AppState::VerifyStatus::VERIFY_EMPTY:
      return "";
    case AppState::VerifyStatus::VERIFY_START:
      return "Touch/Swipe to start Verification";
    case AppState::VerifyStatus::VERIFY_MATCH:
      return "The verification succeeded";
    case AppState::VerifyStatus::VERIFY_NO_MATCH:
      return "The verification did not match";
    case AppState::VerifyStatus::VERIFY_RETRY_SCAN:
      return "Retry scanning the finger";
    case AppState::VerifyStatus::VERIFY_DISCONNECTED:
      return "The device was disconnected during the verification";
    case AppState::VerifyStatus::VERIFY_UNKNOWN_ERROR:
      return "An unknown error occurred";
    case AppState::VerifyStatus::VERIFY_SWIPE_TOO_SHORT:
      return "Swipe was too short";
    case AppState::VerifyStatus::VERIFY_REMOVE_AND_RETRY:
      return "Remove the finger from the reader and retry scanning";
    case AppState::VerifyStatus::VERIFY_FINGER_NOT_CENTERED:
      return "Finger was not centered on the reader";
  }

  return "";
}
