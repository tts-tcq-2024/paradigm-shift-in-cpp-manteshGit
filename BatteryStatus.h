#ifndef BATTERYSTATUS_H
#define BATTERYSTATUS_H

#include "StatusCodes.h"
#include <tuple>

class BatteryStatus {
public:
    static bool batteryIsOk(float soc, float temp, float chargeRate);

private:
    static std::tuple<StatusCode, StatusCode, StatusCode> getStatus(float soc, float temp, float chargeRate);
};

#endif // BATTERYSTATUS_H
