#include "deviceinfo.h"

DeviceInfo::DeviceInfo(QString name, QString scanType, int numEnrollStages,
                       QObject *parent)
    : QObject(parent) {
  this->_name = name;
  this->_scanType = scanType;
  this->_numEnrollStages = numEnrollStages;
}

QString DeviceInfo::name() { return _name; }

QString DeviceInfo::scanType() { return _scanType; }

int DeviceInfo::numEnrollStages() { return _numEnrollStages; }
