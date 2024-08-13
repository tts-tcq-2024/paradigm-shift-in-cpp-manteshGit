#include "BatteryStatus.h"
#include "LanguageSupport.h"

std::tuple<StatusCode, StatusCode, StatusCode> BatteryStatus::getStatus(float soc, float temp, float chargeRate) {
    SOCStatus mSoc;
    TemperatureStatus mTemperature;
    ChargeRateStatus mCharge;
    
    StatusCode socStatus = mSoc.getSOCStatus(soc);
    StatusCode tempStatus = mTemperature.getTemperatureStatus(temp);
    StatusCode chargeRateStatus = mCharge.getChargeRateStatus(chargeRate);

    return std::make_tuple(socStatus, tempStatus, chargeRateStatus);
}

bool BatteryStatus::batteryIsOk(float soc, float temp, float chargeRate) {
    auto status = getStatus(soc, temp, chargeRate);
    StatusCode socStatus = std::get<0>(status);
    StatusCode tempStatus = std::get<1>(status);
    StatusCode chargeRateStatus = std::get<2>(status);

    LanguageSupport::printStatus(soc, temp, chargeRate, socStatus, tempStatus, chargeRateStatus);

    return (socStatus == NORMAL && tempStatus == NORMAL && chargeRateStatus == NORMAL);
}
