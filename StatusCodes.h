#ifndef STATUSCODES_H
#define STATUSCODES_H

#include <string>

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

class Status {
public:
    static constexpr float SOC_MIN = 20.0f;
    static constexpr float SOC_MAX = 80.0f;
    static constexpr float SOC_WARNING_MAX_TOLERANCE = 0.05f * SOC_MAX;
    static constexpr float SOC_WARNING_MIN_TOLERANCE = 0.05f * SOC_MAX;

    static constexpr float TEMP_MAX = 45.0f;
    static constexpr float TEMP_WARNING_TOLERANCE = 0.05f * TEMP_MAX;

    static constexpr float CHARGE_RATE_MAX = 0.8f;
    static constexpr float CHARGE_RATE_WARNING_TOLERANCE = 0.05f * CHARGE_RATE_MAX;

    StatusCode checkSOCBounds(float soc) const;
    StatusCode checkSOCWarnings(float soc) const;
    StatusCode getSOCStatus(float soc) const;

    StatusCode checkTemperatureBounds(float temp) const;
    StatusCode checkTemperatureWarnings(float temp) const;
    StatusCode getTemperatureStatus(float temp) const;

    StatusCode checkChargeRateBounds(float chargeRate) const;
    StatusCode checkChargeRateWarnings(float chargeRate) const;
    StatusCode getChargeRateStatus(float chargeRate) const;
};

#endif // STATUSCODES_H
