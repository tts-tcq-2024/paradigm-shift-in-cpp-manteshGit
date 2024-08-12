#ifndef STATUSCODES_H
#define STATUSCODES_H

#include <string>
#include <iostream>

enum StatusCode {
    NORMAL = 0,
    LOW_SOC_BREACH = 1,
    LOW_SOC_WARNING = 2,
    HIGH_SOC_WARNING = 3,
    HIGH_SOC_BREACH = 4,
    SOC_OUT_OF_RANGE = 5,
    TEMP_OUT_OF_RANGE = 6,
    TEMP_WARNING = 7,
    CHARGE_RATE_WARNING = 8,
    CHARGE_RATE_OUT_OF_RANGE = 9
};

const float SOC_MIN = 20.0f;
const float SOC_MAX = 80.0f;
const float SOC_WARNING_MAX_TOLERANCE = 0.05f * SOC_MAX;
const float SOC_WARNING_MIN_TOLERANCE = 0.05f * SOC_MAX;

const float TEMP_MAX = 45.0f;
const float TEMP_WARNING_TOLERANCE = 0.05f * TEMP_MAX;

const float CHARGE_RATE_MAX = 0.8f;
const float CHARGE_RATE_WARNING_TOLERANCE = 0.05f * CHARGE_RATE_MAX;

StatusCode checkSOCBounds(float soc);
StatusCode checkSOCWarnings(float soc);
StatusCode getSOCStatus(float soc);
StatusCode checkTemperatureBounds(float temp);
StatusCode checkTemperatureWarnings(float temp);
StatusCode getTemperatureStatus(float temp);
StatusCode checkChargeRateBounds(float chargeRate);
StatusCode checkChargeRateWarnings(float chargeRate);
StatusCode getChargeRateStatus(float chargeRate);

#endif // STATUSCODES_H
