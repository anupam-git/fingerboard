#include "logger.h"
#include "../fingerboard_version.h"

#include <QDateTime>
#include <QDebug>
#include <QStandardPaths>
#include <QUrl>

Logger::Logger(QObject *parent) : QObject(parent) {
  file = new QFile(
      QStandardPaths::writableLocation(QStandardPaths::CacheLocation) +
      "/fingerboard.log");
  file->open(QIODevice::WriteOnly | QIODevice::Append);
}

void Logger::log(Logger::Level level, QString msg) {
  QString format = QString("%1 %2 : %3");
  QString logMsg;

  QString timestamp =
      QDateTime::currentDateTime().toString("dd/MMM/yyyy hh:mm:ss");

  switch (level) {
  case Level::INFO:
    qInfo() << msg;
    logMsg = format.arg("[INFO]", 10).arg(timestamp, 22).arg(msg);
    break;

  case Level::DEBUG:
    qDebug() << msg;
    logMsg = format.arg("[DEBUG]", 10).arg(timestamp, 22).arg(msg);
    break;

  case Level::VERBOSE:
    qDebug() << msg;
    logMsg = format.arg("[VERBOSE]", 10).arg(timestamp, 22).arg(msg);
    break;

  case Level::WARNING:
    qWarning() << msg;
    logMsg = format.arg("[WARNING]", 10).arg(timestamp, 22).arg(msg);
    break;

  case Level::CRITICAL:
    qCritical() << msg;
    logMsg = format.arg("[CRITICAL]", 10).arg(timestamp, 22).arg(msg);
    break;
  }

  QTextStream ts(file);
  ts << logMsg << Qt::endl;
}

Logger::~Logger() { file->close(); }
