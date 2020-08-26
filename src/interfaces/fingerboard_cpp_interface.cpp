#include "fingerboard_cpp_interface.h"

#include <QDataStream>
#include <QDebug>

FingerboardCppInterface::FingerboardCppInterface(QObject *parent)
    : QObject(parent) {
  logger = new Logger(parent);
}

void FingerboardCppInterface::listFp() {
  logger->log(Logger::INFO, "Start Listing FP");
  logger->log(Logger::INFO, "End Listing FP");
}

void FingerboardCppInterface::enrollFp() {
  logger->log(Logger::INFO, "Start Enrolling FP");
  logger->log(Logger::INFO, "End Enrolling FP");
}

void FingerboardCppInterface::verifyFp() {
  logger->log(Logger::INFO, "Start Verifying FP");
  logger->log(Logger::INFO, "End Verifying FP");
}

void FingerboardCppInterface::deleteFp() {
  logger->log(Logger::INFO, "Deleting FP");
}
