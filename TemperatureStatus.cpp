#include "TemperatureStatus.h"

TemperatureStatus::TemperatureStatus(bool enableWarnings) {
    setWarningsEnabled(enableWarnings); // Initialize warningsEnabled
}

StatusCode TemperatureStatus::checkTemperatureWarnings(float temp) const {
    if (!areWarningsEnabled()) return NORMAL;
    
    if ((temp > TEMP_MAX - TEMP_WARNING_TOLERANCE) and temp <= TEMP_MAX) {
        return TEMP_WARNING;
    }
    return NORMAL;
}

StatusCode TemperatureStatus::checkTemperatureBounds(float temp) const {
    if (temp > TEMP_MAX) {
        return TEMP_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode TemperatureStatus::getTemperatureStatus(float temp) const {
    StatusCode warningStatus = checkTemperatureWarnings(temp);
    if (warningStatus != NORMAL) return warningStatus;
    return checkTemperatureBounds(temp);
}
