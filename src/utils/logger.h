#ifndef UTILS_LOGGER
#define UTILS_LOGGER

#include <QFile>
#include <QObject>
#include <QString>
#include <QTextStream>

class Logger : public QObject {
  Q_OBJECT

 public:
  enum Level { ERROR = 0, WARNING, INFO, DEBUG, VERBOSE };
  Q_ENUM(Level)

  Logger(QObject *parent = nullptr);
  ~Logger();

  void log(Logger::Level level, QString msg);

 signals:
  void writeLog(Logger::Level logLevel, QString msg);

 private:
  QFile *file;
};

#endif  // UTILS_LOGGER
