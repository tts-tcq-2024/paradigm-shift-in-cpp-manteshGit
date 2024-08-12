#include "StatusCodes.h"

StatusCode Status::checkSOCWarnings(float soc) const {
    if (soc < SOC_MIN + SOC_WARNING_MIN_TOLERANCE) {
        return LOW_SOC_WARNING;
    } else if (soc > SOC_MAX - SOC_WARNING_MAX_TOLERANCE) {
        return HIGH_SOC_WARNING;
    }
    return NORMAL;
}

StatusCode Status::checkSOCBounds(float soc) const {
    if (soc < SOC_MIN || soc > SOC_MAX) {
        return SOC_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode Status::getSOCStatus(float soc) const {
    StatusCode warningStatus = checkSOCWarnings(soc);
    if (warningStatus != NORMAL) return warningStatus;
    return checkSOCBounds(soc);
}

StatusCode Status::checkTemperatureWarnings(float temp) const {
    if (temp > TEMP_MAX - TEMP_WARNING_TOLERANCE) {
        return TEMP_WARNING;
    }
    return NORMAL;
}

StatusCode Status::checkTemperatureBounds(float temp) const {
    if (temp > TEMP_MAX) {
        return TEMP_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode Status::getTemperatureStatus(float temp) const {
    StatusCode warningStatus = checkTemperatureWarnings(temp);
    if (warningStatus != NORMAL) return warningStatus;
    return checkTemperatureBounds(temp);
}

StatusCode Status::checkChargeRateWarnings(float chargeRate) const {
    if (chargeRate > CHARGE_RATE_MAX - CHARGE_RATE_WARNING_TOLERANCE) {
        return CHARGE_RATE_WARNING;
    }
    return NORMAL;
}

StatusCode Status::checkChargeRateBounds(float chargeRate) const {
    if (chargeRate > CHARGE_RATE_MAX) {
        return CHARGE_RATE_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode Status::getChargeRateStatus(float chargeRate) const {
    StatusCode warningStatus = checkChargeRateWarnings(chargeRate);
    if (warningStatus != NORMAL) return warningStatus;
    return checkChargeRateBounds(chargeRate);
}
