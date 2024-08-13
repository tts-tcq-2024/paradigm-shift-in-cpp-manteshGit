#ifndef STATUSUTILS_H
#define STATUSUTILS_H

#include "StatusCodes.h"
#include <string>
#include <vector>

enum class Language {
    ENGLISH,
    GERMAN
};

class LanguageSupport {
public:
    static std::string statusCodeToString(StatusCode status, Language lang = Language::ENGLISH);
    static void printStatus(float soc, float temp, float chargeRate, StatusCode socStatus, StatusCode tempStatus, StatusCode chargeRateStatus, Language lang = Language::ENGLISH);

    static void setLanguage(Language lang) {
        currentLanguage = lang;
    }

private:
    static Language currentLanguage;
    static const std::vector<std::vector<std::string>>& getStatusDescriptions();
};

#endif // STATUSUTILS_H
