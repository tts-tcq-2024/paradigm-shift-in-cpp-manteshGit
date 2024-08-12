#ifndef BATTERYSTATUS_H
#define BATTERYSTATUS_H

#include "statusCodes.h"
#include <tuple>

std::tuple<StatusCode, StatusCode, StatusCode> getStatus(float soc, float temp, float chargeRate);
bool batteryIsOk(float soc, float temp, float chargeRate);

#endif // BATTERYSTATUS_H
