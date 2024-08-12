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
    static std::string statusCodeToString(StatusCode status);
    static void printStatus(float soc, float temp, float chargeRate, StatusCode socStatus, StatusCode tempStatus, StatusCode chargeRateStatus);

    static void setLanguage(Language lang) {
        currentLanguage = lang;
    }

private:
    static Language currentLanguage;
    static const std::map<StatusCode, std::string>& getStatusDescriptions(Language lang = Language::ENGLISH);
};

#endif // STATUSUTILS_H
