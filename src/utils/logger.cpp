#include "logger.h"

#include <QDateTime>
#include <QStandardPaths>
#include <QUrl>

#include "../fingerboard_version.h"

Logger::Logger(QObject *parent) : QObject(parent) {
  file = new QFile(
      QStandardPaths::writableLocation(QStandardPaths::CacheLocation) +
      "/fingerboard.log");
  file->open(QIODevice::WriteOnly | QIODevice::Append);
}

void Logger::log(Logger::Level level, QString msg) {
  QString format = QString("%1 %2 : %3");
  QString logLevel = "";

  QString timestamp =
      QDateTime::currentDateTime().toString("dd/MMM/yyyy hh:mm:ss");

  switch (level) {
    case Level::INFO:
      logLevel = "[INFO]";
      break;

    case Level::DEBUG:
      logLevel = "[DEBUG]";
      break;

    case Level::VERBOSE:
      logLevel = "[VERBOSE]";
      break;

    case Level::WARNING:
      logLevel = "[WARNING]";
      break;

    case Level::ERROR:
      logLevel = "[ERROR]";
      break;
  }

  QString logMsg = format.arg(logLevel, 10).arg(timestamp, 22).arg(msg);
  QTextStream ts(file);
  ts << logMsg << Qt::endl;

  emit writeLog(level, logMsg);
}

Logger::~Logger() { file->close(); }
