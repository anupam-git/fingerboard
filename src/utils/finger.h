#ifndef UTILS_FINGER_H
#define UTILS_FINGER_H

#include <QMap>
#include <QObject>

class Finger : public QObject {
  Q_OBJECT

 public:
  enum Fingerprint {
    LEFT_THUMB,
    LEFT_INDEX,
    LEFT_MIDDLE,
    LEFT_RING,
    LEFT_LITTLE,
    RIGHT_THUMB,
    RIGHT_INDEX,
    RIGHT_MIDDLE,
    RIGHT_RING,
    RIGHT_LITTLE
  };
  Q_ENUM(Fingerprint)

  Finger(QObject *parent = nullptr);

  QString name(Fingerprint finger);
  Fingerprint fromName(QString rawFingerName);

 private:
  QMap<QString, Fingerprint> rawFingersMap = {
      {"left-thumb", Fingerprint::LEFT_THUMB},
      {"left-index-finger", Fingerprint::LEFT_INDEX},
      {"left-middle-finger", Fingerprint::LEFT_MIDDLE},
      {"left-ring-finger", Fingerprint::LEFT_RING},
      {"left-little-finger", Fingerprint::LEFT_LITTLE},

      {"right-thumb", Fingerprint::RIGHT_THUMB},
      {"right-index-finger", Fingerprint::RIGHT_INDEX},
      {"right-middle-finger", Fingerprint::RIGHT_MIDDLE},
      {"right-ring-finger", Fingerprint::RIGHT_RING},
      {"right-little-finger", Fingerprint::RIGHT_LITTLE},
  };
};

#endif  // UTILS_FINGER_H
