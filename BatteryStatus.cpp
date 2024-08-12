#include "BatteryStatus.h"
#include "StatusUtils.h"

std::tuple<StatusCode, StatusCode, StatusCode> BatteryStatus::getStatus(float soc, float temp, float chargeRate) {
    Status status;
    StatusCode socStatus = status.getSOCStatus(soc);
    StatusCode tempStatus = status.getTemperatureStatus(temp);
    StatusCode chargeRateStatus = status.getChargeRateStatus(chargeRate);

    return std::make_tuple(socStatus, tempStatus, chargeRateStatus);
}

bool BatteryStatus::batteryIsOk(float soc, float temp, float chargeRate) {
    auto status = getStatus(soc, temp, chargeRate);
    StatusCode socStatus = std::get<0>(status);
    StatusCode tempStatus = std::get<1>(status);
    StatusCode chargeRateStatus = std::get<2>(status);

    StatusUtils::printStatus(soc, temp, chargeRate, socStatus, tempStatus, chargeRateStatus);

    return (socStatus == NORMAL && tempStatus == NORMAL && chargeRateStatus == NORMAL);
}
