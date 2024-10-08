#include "SOCStatus.h"

SOCStatus::SOCStatus(bool enableWarnings) {
    setWarningsEnabled(enableWarnings); // Initialize warningsEnabled
}

StatusCode SOCStatus::checkSOCWarnings(float soc) const {
    if ((soc < SOC_MIN + SOC_WARNING_MIN_TOLERANCE) and soc >= SOC_MIN and areWarningsEnabled()) {
        return LOW_SOC_WARNING;
    } else if ((soc > (SOC_MAX - SOC_WARNING_MAX_TOLERANCE)) and soc <= SOC_MAX and areWarningsEnabled()) {
        return HIGH_SOC_WARNING;
    }
    return NORMAL;
}

StatusCode SOCStatus::checkSOCBounds(float soc) const {
    if (soc < SOC_MIN || soc > SOC_MAX) {
        return SOC_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode SOCStatus::getSOCStatus(float soc) const {
    StatusCode warningStatus = checkSOCWarnings(soc);
    if (warningStatus != NORMAL) return warningStatus;
    return checkSOCBounds(soc);
}
