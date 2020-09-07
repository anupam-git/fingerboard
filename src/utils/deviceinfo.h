#ifndef UTILS_DEVICEINFO_H
#define UTILS_DEVICEINFO_H

#include <QObject>

class DeviceInfo : public QObject {
  Q_OBJECT

 public:
  DeviceInfo(QString name, QString scanType, int numEnrollStages,
             QObject *parent = nullptr);

 public slots:
  QString name();
  QString scanType();
  int numEnrollStages();

 private:
  QString _name;
};

#endif  // UTILS_DEVICEINFO_H
