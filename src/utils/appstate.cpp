#include "appstate.h"

AppState::AppState(QObject *parent) : QObject(parent) {
  this->_state = State::INIT;
}

AppState::State AppState::getState() { return this->_state; }
void AppState::setState(AppState::State state) { this->_state = state; }
