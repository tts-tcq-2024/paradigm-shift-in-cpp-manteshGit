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

#endif // STATUSCODES_H
