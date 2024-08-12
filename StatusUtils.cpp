#include "StatusUtils.h"
#include <iostream>

// Initialize the default language
Language StatusUtils::currentLanguage = Language::ENGLISH;

// Multidimensional vector to hold descriptions for each status code and language
const std::vector<std::vector<std::string>> statusDescriptions = {
    // English descriptions
    {
        "NORMAL",
        "LOW_SOC_BREACH",
        "LOW_SOC_WARNING: Approaching discharge",
        "HIGH_SOC_WARNING: Approaching charge-peak",
        "HIGH_SOC_BREACH",
        "SOC_OUT_OF_RANGE",
        "TEMP_WARNING: Approaching maximum temperature",
        "TEMP_OUT_OF_RANGE",
        "CHARGE_RATE_WARNING: Approaching maximum charge rate",
        "CHARGE_RATE_OUT_OF_RANGE"
    },
    // German descriptions
    {
        "NORMAL",
        "NIEDRIGER SOC ÜBERSCHREITUNG",
        "NIEDRIGER SOC WARNUNG: Näher am Entladen",
        "HOHER SOC WARNUNG: Näher am Ladepeak",
        "HOHER SOC ÜBERSCHREITUNG",
        "SOC AUF DEM BEREICH",
        "TEMPERATURWARNUNG: Näher an der maximalen Temperatur",
        "TEMPERATUR AUF DEM BEREICH",
        "LADRATENWARNUNG: Näher an der maximalen Ladegeschwindigkeit",
        "LADRATEN AUF DEM BEREICH"
    }
};

const std::vector<std::vector<std::string>>& StatusUtils::getStatusDescriptions() {
    return statusDescriptions;
}

std::string StatusUtils::statusCodeToString(StatusCode status, Language lang) {
    const std::vector<std::string>& descriptions = getStatusDescriptions()[static_cast<int>(lang)];

    if (status >= 0 && status < descriptions.size()) {
        return descriptions[status];
    }
    return "UNKNOWN STATUS";
}

void StatusUtils::printStatus(float soc, float temp, float chargeRate, StatusCode socStatus, StatusCode tempStatus, StatusCode chargeRateStatus, Language lang) {
    std::cout << "SOC: " << soc << ", Temp: " << temp << ", Charge Rate: " << chargeRate
              << " -> SOC Status: " << statusCodeToString(socStatus, lang)
              << ", Temp Status: " << statusCodeToString(tempStatus, lang)
              << ", Charge Rate Status: " << statusCodeToString(chargeRateStatus, lang) << std::endl;
}
