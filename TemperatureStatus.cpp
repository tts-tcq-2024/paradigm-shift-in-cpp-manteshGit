#include "TemperatureStatus.h"

StatusCode TemperatureStatus::checkTemperatureWarnings(float temp) const {
    if (temp > TEMP_MAX - TEMP_WARNING_TOLERANCE) {
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
