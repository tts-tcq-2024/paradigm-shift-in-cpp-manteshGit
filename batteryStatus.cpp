#include "batteryStatus.h"
#include "statusCodes.h"
#include "statusUtils.h"
#include <tuple>
#include <iostream>

std::tuple<StatusCode, StatusCode, StatusCode> getStatus(float soc, float temp, float chargeRate) {
    StatusCode socStatus = getSOCStatus(soc);
    StatusCode tempStatus = getTemperatureStatus(temp);
    StatusCode chargeRateStatus = getChargeRateStatus(chargeRate);

    return std::make_tuple(socStatus, tempStatus, chargeRateStatus);
}

bool batteryIsOk(float soc, float temp, float chargeRate) {
    auto status = getStatus(soc, temp, chargeRate);
    StatusCode socStatus = std::get<0>(status);
    StatusCode tempStatus = std::get<1>(status);
    StatusCode chargeRateStatus = std::get<2>(status);

    printStatus(soc, temp, chargeRate, socStatus, tempStatus, chargeRateStatus);

    return (socStatus == NORMAL && tempStatus == NORMAL && chargeRateStatus == NORMAL);
}
