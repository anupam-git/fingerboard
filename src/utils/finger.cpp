#include "finger.h"

Finger::Finger(QObject *parent) : QObject(parent) {}

QString Finger::name(Finger::Fingerprint finger) {
  switch (finger) {
    case Finger::Fingerprint::LEFT_THUMB:
      return "Left Thumb";
    case Finger::Fingerprint::LEFT_INDEX:
      return "Left Index Finger";
    case Finger::Fingerprint::LEFT_MIDDLE:
      return "Left Middle Finger";
    case Finger::Fingerprint::LEFT_RING:
      return "Left Ring Finger";
    case Finger::Fingerprint::LEFT_LITTLE:
      return "Left Little Finger";
    case Finger::Fingerprint::RIGHT_THUMB:
      return "Right Thumb";
    case Finger::Fingerprint::RIGHT_INDEX:
      return "Right Index Finger";
    case Finger::Fingerprint::RIGHT_MIDDLE:
      return "Right Middle Finger";
    case Finger::Fingerprint::RIGHT_RING:
      return "Right Ring Finger";
    case Finger::Fingerprint::RIGHT_LITTLE:
      return "Right Little Finger";
  }

  return "";
}

Finger::Fingerprint Finger::fromName(QString rawFingerName) {
  return rawFingersMap[rawFingerName];
}
