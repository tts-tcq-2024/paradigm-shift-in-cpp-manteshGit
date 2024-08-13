#ifndef CHARGERATESTATUS_H
#define CHARGERATESTATUS_H

#include "StatusCodes.h"  // Include for StatusCode enum

class ChargeRateStatus {
private:
    static constexpr float CHARGE_RATE_MAX = 0.8f;
    static constexpr float CHARGE_RATE_WARNING_TOLERANCE = 0.05f * CHARGE_RATE_MAX;
public:
    StatusCode checkChargeRateWarnings(float chargeRate) const;
    StatusCode checkChargeRateBounds(float chargeRate) const;
    StatusCode getChargeRateStatus(float chargeRate) const;
};

#endif // CHARGERATESTATUS_H
