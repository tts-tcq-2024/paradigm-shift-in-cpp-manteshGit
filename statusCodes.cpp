#include "statusCodes.h"

StatusCode checkSOCBounds(float soc) {
    if (soc < SOC_MIN || soc > SOC_MAX) {
        return SOC_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode checkSOCWarnings(float soc) {
    if (soc < SOC_MIN + SOC_WARNING_MIN_TOLERANCE) {
        return LOW_SOC_WARNING;
    } else if (soc > SOC_MAX - SOC_WARNING_MAX_TOLERANCE) {
        return HIGH_SOC_WARNING;
    }
    return NORMAL;
}

StatusCode getSOCStatus(float soc) {
    StatusCode boundsStatus = checkSOCBounds(soc);
    if (boundsStatus != NORMAL) return boundsStatus;
    return checkSOCWarnings(soc);
}

StatusCode checkTemperatureBounds(float temp) {
    if (temp > TEMP_MAX) {
        return TEMP_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode checkTemperatureWarnings(float temp) {
    if (temp > TEMP_MAX - TEMP_WARNING_TOLERANCE) {
        return TEMP_WARNING;
    }
    return NORMAL;
}

StatusCode getTemperatureStatus(float temp) {
    StatusCode boundsStatus = checkTemperatureBounds(temp);
    if (boundsStatus != NORMAL) return boundsStatus;
    return checkTemperatureWarnings(temp);
}

StatusCode checkChargeRateBounds(float chargeRate) {
    if (chargeRate > CHARGE_RATE_MAX) {
        return CHARGE_RATE_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode checkChargeRateWarnings(float chargeRate) {
    if (chargeRate > CHARGE_RATE_MAX - CHARGE_RATE_WARNING_TOLERANCE) {
        return CHARGE_RATE_WARNING;
    }
    return NORMAL;
}

StatusCode getChargeRateStatus(float chargeRate) {
    StatusCode boundsStatus = checkChargeRateBounds(chargeRate);
    if (boundsStatus != NORMAL) return boundsStatus;
    return checkChargeRateWarnings(chargeRate);
}
