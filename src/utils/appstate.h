#ifndef UTILS_APPSTATE_H
#define UTILS_APPSTATE_H

#include <QObject>
#include <QString>

class AppState : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      AppState::State state READ getState WRITE setState NOTIFY stateChanged)

 public:
  enum State { INIT, IDLE, ERROR, ENROLLING, VERIFYING, DELETING, LISTING };
  Q_ENUM(State);

  AppState(QObject *parent = nullptr);

  AppState::State getState();
  void setState(AppState::State state);

 signals:
  void stateChanged();

 private:
  AppState::State _state;
};

#endif  // UTILS_APPSTATE_H
