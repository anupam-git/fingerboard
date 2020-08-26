#include "fingerboard_cpp_interface.h"

#include <QDataStream>
#include <QDebug>

FingerboardCppInterface::FingerboardCppInterface(QObject *parent)
    : QObject(parent) {
  logger = new Logger(parent);
}

void FingerboardCppInterface::listFp() {
  logger->log(Logger::INFO, "Start Listing FP");
  logger->log(Logger::DEBUG, "End Listing FP");
}

void FingerboardCppInterface::enrollFp() {
  logger->log(Logger::VERBOSE, "Start Enroll FP");
  logger->log(Logger::CRITICAL, "End Enroll FP");
}

void FingerboardCppInterface::verifyFp() {
  logger->log(Logger::WARNING, "Start Verify FP");
  logger->log(Logger::DEBUG, "End Verify FP");
}

void FingerboardCppInterface::deleteFp() {
  logger->log(Logger::DEBUG, "Delete FP");
}
