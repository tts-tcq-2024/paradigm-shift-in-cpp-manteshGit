#include "statusUtils.h"
#include <map>
#include <iostream>

std::map<StatusCode, std::string> createStatusDescriptionMap() {
    std::map<StatusCode, std::string> statusDescriptions;
    statusDescriptions[NORMAL] = "NORMAL";
    statusDescriptions[LOW_SOC_BREACH] = "LOW_SOC_BREACH";
    statusDescriptions[LOW_SOC_WARNING] = "LOW_SOC_WARNING: Approaching discharge";
    statusDescriptions[HIGH_SOC_WARNING] = "HIGH_SOC_WARNING: Approaching charge-peak";
    statusDescriptions[HIGH_SOC_BREACH] = "HIGH_SOC_BREACH";
    statusDescriptions[SOC_OUT_OF_RANGE] = "SOC_OUT_OF_RANGE";
    statusDescriptions[TEMP_WARNING] = "TEMP_WARNING: Approaching maximum temperature";
    statusDescriptions[TEMP_OUT_OF_RANGE] = "TEMP_OUT_OF_RANGE";
    statusDescriptions[CHARGE_RATE_WARNING] = "CHARGE_RATE_WARNING: Approaching maximum charge rate";
    statusDescriptions[CHARGE_RATE_OUT_OF_RANGE] = "CHARGE_RATE_OUT_OF_RANGE";
    return statusDescriptions;
}

std::string statusCodeToString(StatusCode status) {
    auto statusDescriptions = createStatusDescriptionMap();
    return statusDescriptions.at(status);
}

void printStatus(float soc, float temp, float chargeRate, StatusCode socStatus, StatusCode tempStatus, StatusCode chargeRateStatus) {
    std::cout << "SOC: " << soc << ", Temp: " << temp << ", Charge Rate: " << chargeRate
              << " -> SOC Status: " << statusCodeToString(socStatus)
              << ", Temp Status: " << statusCodeToString(tempStatus)
              << ", Charge Rate Status: " << statusCodeToString(chargeRateStatus) << std::endl;
}
