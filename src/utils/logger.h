#ifndef UTILS_LOGGER
#define UTILS_LOGGER

#include <QFile>
#include <QObject>
#include <QString>
#include <QTextStream>

class Logger : public QObject {
  Q_OBJECT

 public:
  enum Level { INFO, DEBUG, VERBOSE, WARNING, CRITICAL };

  Logger(QObject *parent = nullptr);
  ~Logger();

  void log(Level level, QString msg);

 signals:
  void writeLog(QString msg);

 private:
  QFile *file;
};

#endif  // UTILS_LOGGER
