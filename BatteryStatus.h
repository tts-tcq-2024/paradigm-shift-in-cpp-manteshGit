#ifndef BATTERYSTATUS_H
#define BATTERYSTATUS_H

#include "StatusCodes.h"
#include <tuple>

namespace BatteryStatus {
    bool batteryIsOk(float soc, float temp, float chargeRate);
    std::tuple<StatusCode, StatusCode, StatusCode> getStatus(float soc, float temp, float chargeRate);
};

#endif // BATTERYSTATUS_H
