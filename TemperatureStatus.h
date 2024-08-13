#ifndef TEMPERATURESTATUS_H
#define TEMPERATURESTATUS_H

#include "StatusCodes.h"  // Include for StatusCode enum

class TemperatureStatus : public StatusCodes {
private:
    static constexpr float TEMP_MAX = 45.0f;
    static constexpr float TEMP_WARNING_TOLERANCE = 0.05f * TEMP_MAX;
public:
    TemperatureStatus(bool enableWarnings = true);
    
    StatusCode checkTemperatureWarnings(float temp) const;
    StatusCode checkTemperatureBounds(float temp) const;
    StatusCode getTemperatureStatus(float temp) const;
};

#endif // TEMPERATURESTATUS_H
