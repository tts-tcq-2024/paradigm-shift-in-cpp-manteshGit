#include "statusUtils.h"
#include <map>
#include <iostream>

// Define translation maps for different languages
const std::map<StatusCode, std::string> englishStatusDescriptions = {
    {NORMAL, "NORMAL"},
    {LOW_SOC_BREACH, "LOW_SOC_BREACH"},
    {LOW_SOC_WARNING, "LOW_SOC_WARNING: Approaching discharge"},
    {HIGH_SOC_WARNING, "HIGH_SOC_WARNING: Approaching charge-peak"},
    {HIGH_SOC_BREACH, "HIGH_SOC_BREACH"},
    {SOC_OUT_OF_RANGE, "SOC_OUT_OF_RANGE"},
    {TEMP_WARNING, "TEMP_WARNING: Approaching maximum temperature"},
    {TEMP_OUT_OF_RANGE, "TEMP_OUT_OF_RANGE"},
    {CHARGE_RATE_WARNING, "CHARGE_RATE_WARNING: Approaching maximum charge rate"},
    {CHARGE_RATE_OUT_OF_RANGE, "CHARGE_RATE_OUT_OF_RANGE"}
};

const std::map<StatusCode, std::string> germanStatusDescriptions = {
    {NORMAL, "NORMAL"},
    {LOW_SOC_BREACH, "NIEDRIGER SOC ÜBERSCHREITUNG"},
    {LOW_SOC_WARNING, "NIEDRIGER SOC WARNUNG: Näher am Entladen"},
    {HIGH_SOC_WARNING, "HOHER SOC WARNUNG: Näher am Ladepeak"},
    {HIGH_SOC_BREACH, "HOHER SOC ÜBERSCHREITUNG"},
    {SOC_OUT_OF_RANGE, "SOC AUF DEM BEREICH"},
    {TEMP_WARNING, "TEMPERATURWARNUNG: Näher an der maximalen Temperatur"},
    {TEMP_OUT_OF_RANGE, "TEMPERATUR AUF DEM BEREICH"},
    {CHARGE_RATE_WARNING, "LADRATENWARNUNG: Näher an der maximalen Ladegeschwindigkeit"},
    {CHARGE_RATE_OUT_OF_RANGE, "LADRATEN AUF DEM BEREICH"}
};

std::string statusCodeToString(StatusCode status, Language lang) {
    const std::map<StatusCode, std::string>* descriptions = &englishStatusDescriptions;
    
    if (lang == Language::GERMAN) {
        descriptions = &germanStatusDescriptions;
    }
    
    auto it = descriptions->find(status);
    if (it != descriptions->end()) {
        return it->second;
    }
    return "UNKNOWN STATUS";
}

void printStatus(float soc, float temp, float chargeRate, StatusCode socStatus, StatusCode tempStatus, StatusCode chargeRateStatus) {
    std::cout << "SOC: " << soc << ", Temp: " << temp << ", Charge Rate: " << chargeRate
              << " -> SOC Status: " << statusCodeToString(socStatus)
              << ", Temp Status: " << statusCodeToString(tempStatus)
              << ", Charge Rate Status: " << statusCodeToString(chargeRateStatus) << std::endl;
}
