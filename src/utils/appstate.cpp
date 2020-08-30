#include "appstate.h"

AppState::AppState(QObject *parent) : QObject(parent) {}

QString AppState::errorStatusString(AppState::ErrorStatus status) {
  switch (status) {
    case AppState::ErrorStatus::ERROR_NONE:
      return "";

    // LIST
    case AppState::ErrorStatus::ERROR_LIST_PERMISSION_DENIED:
      return "User lacks the appropriate PolicyKit authorization";
    case AppState::ErrorStatus::ERROR_LIST_NO_ENROLLED_PRINTS:
      return "User doesn't have any fingerprints enrolled";
    // END LIST

    // DELETE
    case AppState::ErrorStatus::ERROR_DELETE_PERMISSION_DENIED:
      return "User lacks the appropriate PolicyKit authorization";
    // END DELETE

    // CLAIM
    case AppState::ErrorStatus::ERROR_CLAIM_PERMISSION_DENIED:
      return "User lacks the appropriate PolicyKit authorization";
    case AppState::ErrorStatus::ERROR_CLAIM_ALREADY_IN_USE:
      return "Device is already claimed";
    case AppState::ErrorStatus::ERROR_CLAIM_INTERNAL:
      return "Device couldn't be claimed";
    // END CLAIM

    // RELEASE
    case AppState::ErrorStatus::ERROR_RELEASE_PERMISSION_DENIED:
      return "User lacks the appropriate PolicyKit authorization";
    case AppState::ErrorStatus::ERROR_RELEASE_CLAIM_DEVICE:
      return "Device was not claimed";
    // EMD RELEASE

    // VERIFY
    case AppState::ErrorStatus::ERROR_VERIFY_PERMISSION_DENIED:
      return "User lacks the appropriate PolicyKit authorization";
    case AppState::ErrorStatus::ERROR_VERIFY_CLAIM_DEVICE:
      return "Device was not claimed";
    case AppState::ErrorStatus::ERROR_VERIFY_ALREADY_IN_USE:
      return "Device is already being used by another application or user";
    case AppState::ErrorStatus::ERROR_VERIFY_NO_ENROLLED_PRINTS:
      return "User doesn't have any fingerprints enrolled";
    case AppState::ErrorStatus::ERROR_VERIFY_NO_ACTION_IN_PROGRESS:
      return "There are no ongoing verification";
    case AppState::ErrorStatus::ERROR_VERIFY_INTERNAL:
      return "Internal error occured";
    // END VERIFY

    // ENROLL
    case AppState::ErrorStatus::ERROR_ENROLL_PERMISSION_DENIED:
      return "User lacks the appropriate PolicyKit authorization";
    case AppState::ErrorStatus::ERROR_ENROLL_CLAIM_DEVICE:
      return "Device was not claimed";
    case AppState::ErrorStatus::ERROR_ENROLL_ALREADY_IN_USE:
      return "Device is already being used by another application or user";
    case AppState::ErrorStatus::ERROR_ENROLL_INVALID_FINGERNAME:
      return "Finger name passed is invalid";
    case AppState::ErrorStatus::ERROR_ENROLL_NO_ACTION_IN_PROGRESS:
      return "There are no ongoing verification";
    case AppState::ErrorStatus::ERROR_ENROLL_INTERNAL:
      return "Internal error occured";
      // END ENROLL
  }

  return "";
}

QString AppState::enrollStatusString(AppState::EnrollStatus status) {
  switch (status) {
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

QString AppState::verifyStatusString(AppState::VerifyStatus status) {
  switch (status) {
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

QString AppState::fingerString(AppState::Finger finger) {
  switch (finger) {
    case AppState::Finger::FINGER_LEFT_THUMB:
      return "Left Thumb";
    case AppState::Finger::FINGER_LEFT_INDEX:
      return "Left Index Finger";
    case AppState::Finger::FINGER_LEFT_MIDDLE:
      return "Left Middle Finger";
    case AppState::Finger::FINGER_LEFT_RING:
      return "Left Ring Finger";
    case AppState::Finger::FINGER_LEFT_LITTLE:
      return "Left Little Finger";
    case AppState::Finger::FINGER_RIGHT_THUMB:
      return "Right Thumb";
    case AppState::Finger::FINGER_RIGHT_INDEX:
      return "Right Index Finger";
    case AppState::Finger::FINGER_RIGHT_MIDDLE:
      return "Right Middle Finger";
    case AppState::Finger::FINGER_RIGHT_RING:
      return "Right Ring Finger";
    case AppState::Finger::FINGER_RIGHT_LITTLE:
      return "Right Little Finger";
  }

  return "";
}
