#ifndef REGISTERTYPES_H
#define REGISTERTYPES_H

#include <QObject>

#include "interfaces/fingerboard_cpp_interface.h"
#include "utils/appstate.h"
#include "utils/finger.h"

void registerQmlTypes(QObject* parent = nullptr);

#endif // REGISTERTYPES_H
