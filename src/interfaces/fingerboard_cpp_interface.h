#ifndef INTERFACES_FINGERBOARD_CPP_INTERFACE
#define INTERFACES_FINGERBOARD_CPP_INTERFACE

#include "utils/logger.h"

#include <QObject>

class FingerboardCppInterface : public QObject {
  Q_OBJECT

public:
  FingerboardCppInterface(QObject *parent = nullptr);
  Logger *logger;

public slots:
  void listFp();
  void enrollFp();
  void verifyFp();
  void deleteFp();
};

#endif // INTERFACES_FINGERBOARD_CPP_INTERFACE
