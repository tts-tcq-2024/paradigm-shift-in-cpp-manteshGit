#ifndef SOCSTATUS_H
#define SOCSTATUS_H

#include "StatusCodes.h"  // Include for StatusCode enum

class SOCStatus {
private:
    // SOC related constants
    static constexpr float SOC_MIN = 20.0f;
    static constexpr float SOC_MAX = 80.0f;
    static constexpr float SOC_WARNING_MAX_TOLERANCE = 0.05f * SOC_MAX;
    static constexpr float SOC_WARNING_MIN_TOLERANCE = 0.05f * SOC_MAX;
public:
    StatusCode checkSOCWarnings(float soc) const;
    StatusCode checkSOCBounds(float soc) const;
    StatusCode getSOCStatus(float soc) const;
};

#endif // SOCSTATUS_H
