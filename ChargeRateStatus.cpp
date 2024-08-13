#include "ChargeRateStatus.h"

ChargeRateStatus::ChargeRateStatus(bool enableWarnings) {
    setWarningsEnabled(enableWarnings); // Initialize warningsEnabled
}

StatusCode ChargeRateStatus::checkChargeRateWarnings(float chargeRate) const {
    if (!areWarningsEnabled()) return NORMAL;
    
    if ((chargeRate >= CHARGE_RATE_MAX - CHARGE_RATE_WARNING_TOLERANCE) and chargeRate <= CHARGE_RATE_MAX) {
        return CHARGE_RATE_WARNING;
    }
    return NORMAL;
}

StatusCode ChargeRateStatus::checkChargeRateBounds(float chargeRate) const {
    if (chargeRate > CHARGE_RATE_MAX) {
        return CHARGE_RATE_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode ChargeRateStatus::getChargeRateStatus(float chargeRate) const {
    StatusCode warningStatus = checkChargeRateWarnings(chargeRate);
    if (warningStatus != NORMAL) return warningStatus;
    return checkChargeRateBounds(chargeRate);
}
