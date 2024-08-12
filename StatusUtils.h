#ifndef STATUSUTILS_H
#define STATUSUTILS_H

#include "StatusCodes.h"
#include <string>
#include <map>

enum class Language {
    ENGLISH,
    GERMAN
};

class StatusUtils {
public:
    static std::string statusCodeToString(StatusCode status, Language lang = Language::ENGLISH);
    static void printStatus(float soc, float temp, float chargeRate, StatusCode socStatus, StatusCode tempStatus, StatusCode chargeRateStatus);
};

#endif // STATUSUTILS_H
