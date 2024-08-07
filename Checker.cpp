#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <cassert>

const float SOC_MIN = 20.0f;
const float SOC_MAX = 80.0f;
const float SOC_WARNING_MAX_TOLERANCE = 0.05f * SOC_MAX;
const float SOC_WARNING_MIN_TOLERANCE = 0.05f * SOC_MAX;

const float TEMP_MAX = 45.0f;
const float TEMP_WARNING_TOLERANCE = 0.05f * TEMP_MAX;

const float CHARGE_RATE_MAX = 0.8f;
const float CHARGE_RATE_WARNING_TOLERANCE = 0.05f * CHARGE_RATE_MAX;

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

StatusCode checkSOCBounds(float soc) {
    if (soc < SOC_MIN || soc > SOC_MAX) {
        return SOC_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode checkSOCWarnings(float soc) {
    if (soc < SOC_MIN + SOC_WARNING_MIN_TOLERANCE) {
        return LOW_SOC_WARNING;
    } else if (soc > SOC_MAX - SOC_WARNING_MAX_TOLERANCE) {
        return HIGH_SOC_WARNING;
    }
    return NORMAL;
}

StatusCode getSOCStatus(float soc) {
    StatusCode boundsStatus = checkSOCBounds(soc);
    if (boundsStatus != NORMAL) return boundsStatus;
    return checkSOCWarnings(soc);
}

StatusCode checkTemperatureBounds(float temp) {
    if (temp > TEMP_MAX) {
        return TEMP_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode checkTemperatureWarnings(float temp) {
    if (temp > TEMP_MAX - TEMP_WARNING_TOLERANCE) {
        return TEMP_WARNING;
    }
    return NORMAL;
}

StatusCode getTemperatureStatus(float temp) {
    StatusCode boundsStatus = checkTemperatureBounds(temp);
    if (boundsStatus != NORMAL) return boundsStatus;
    return checkTemperatureWarnings(temp);
}

StatusCode checkChargeRateBounds(float chargeRate) {
    if (chargeRate > CHARGE_RATE_MAX) {
        return CHARGE_RATE_OUT_OF_RANGE;
    }
    return NORMAL;
}

StatusCode checkChargeRateWarnings(float chargeRate) {
    if (chargeRate > CHARGE_RATE_MAX - CHARGE_RATE_WARNING_TOLERANCE) {
        return CHARGE_RATE_WARNING;
    }
    return NORMAL;
}

StatusCode getChargeRateStatus(float chargeRate) {
    StatusCode boundsStatus = checkChargeRateBounds(chargeRate);
    if (boundsStatus != NORMAL) return boundsStatus;
    return checkChargeRateWarnings(chargeRate);
}

std::tuple<StatusCode, StatusCode, StatusCode> getStatus(float soc, float temp, float chargeRate) {
    StatusCode socStatus = getSOCStatus(soc);
    StatusCode tempStatus = getTemperatureStatus(temp);
    StatusCode chargeRateStatus = getChargeRateStatus(chargeRate);

    return std::make_tuple(socStatus, tempStatus, chargeRateStatus);
}

std::string statusCodeToString(StatusCode status) {
    auto statusDescriptions = createStatusDescriptionMap();
    return statusDescriptions.at(status);
}

auto printStatus = [](float soc, float temp, float chargeRate, StatusCode socStatus, StatusCode tempStatus, StatusCode chargeRateStatus) {
        std::cout << "SOC: " << soc << ", Temp: " << temp << ", Charge Rate: " << chargeRate
                  << " -> SOC Status: " << statusCodeToString(socStatus)
                  << ", Temp Status: " << statusCodeToString(tempStatus)
                  << ", Charge Rate Status: " << statusCodeToString(chargeRateStatus) << std::endl;
    };

bool batteryIsOk(float soc, float temp, float chargeRate) {
    auto status = getStatus(soc, temp, chargeRate);
    StatusCode socStatus = std::get<0>(status);
    StatusCode tempStatus = std::get<1>(status);
    StatusCode chargeRateStatus = std::get<2>(status);

    printStatus(soc, temp, chargeRate, socStatus, tempStatus, chargeRateStatus);

    return (socStatus == NORMAL && tempStatus == NORMAL && chargeRateStatus == NORMAL);
}


int main() {
    assert(batteryIsOk(25, 40, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    assert(batteryIsOk(22, 30, 0.5) == false);
    assert(batteryIsOk(0, 20, 0.9) == false);
    assert(batteryIsOk(35, 75, 0.85) == false);
    assert(batteryIsOk(20, 45, 0.8) == false);
    assert(batteryIsOk(80, 45, 0.8) == false);
    assert(batteryIsOk(19, 30, 0.79) == false);
    assert(batteryIsOk(21, 46, 0.81) == false);
    assert(batteryIsOk(25, 42, 0.76) == true);
    assert(batteryIsOk(24.5, 44, 0.77) == false);
    assert(batteryIsOk(22, 33, 0.75) == false);

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
