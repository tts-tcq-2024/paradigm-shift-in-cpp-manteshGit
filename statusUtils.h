#ifndef STATUSUTILS_H
#define STATUSUTILS_H

#include "statusCodes.h"
#include <string>
#include <tuple>
#include <map>

// Define supported languages
enum class Language {
    ENGLISH,
    GERMAN
};

std::string statusCodeToString(StatusCode status, Language lang = Language::ENGLISH);
void printStatus(float soc, float temp, float chargeRate, StatusCode socStatus, StatusCode tempStatus, StatusCode chargeRateStatus);


#endif // STATUSUTILS_H
