#include <iostream>
#include <map>
#include <string>
#include <cassert>

// Define thresholds and tolerances
const float SOC_MIN = 20.0f;
const float SOC_MAX = 80.0f;
const float SOC_WARNING_MAX_TOLERANCE = 0.05f * SOC_MAX; // 5% tolerance at the upper limit
const float SOC_WARNING_MIN_TOLERANCE = 0.05f * SOC_MIN; // 5% tolerance at the lower limit

const float TEMP_MAX = 45.0f;
const float TEMP_WARNING_TOLERANCE = 0.05f * TEMP_MAX; // 5% tolerance

const float CHARGE_RATE_MAX = 0.8f;
const float CHARGE_RATE_WARNING_TOLERANCE = 0.05f * CHARGE_RATE_MAX; // 5% tolerance

// Define status codes
enum StatusCode {
    LOW_SOC_BREACH = 0,
    LOW_SOC_WARNING = 1,
    NORMAL = 2,
    HIGH_SOC_WARNING = 3,
    HIGH_SOC_BREACH = 4,
    SOC_OUT_OF_RANGE = 5,
    TEMP_OUT_OF_RANGE = 6,
    TEMP_WARNING = 7,
    CHARGE_RATE_WARNING = 8,
    CHARGE_RATE_OUT_OF_RANGE = 9
};

// Define status descriptions
std::map<StatusCode, std::string> createStatusDescriptionMap() {
    std::map<StatusCode, std::string> statusDescriptions;
    statusDescriptions[LOW_SOC_BREACH] = "LOW_SOC_BREACH";
    statusDescriptions[LOW_SOC_WARNING] = "LOW_SOC_WARNING: Approaching discharge";
    statusDescriptions[NORMAL] = "NORMAL";
    statusDescriptions[HIGH_SOC_WARNING] = "HIGH_SOC_WARNING: Approaching charge-peak";
    statusDescriptions[HIGH_SOC_BREACH] = "HIGH_SOC_BREACH";
    statusDescriptions[SOC_OUT_OF_RANGE] = "SOC_OUT_OF_RANGE";
    statusDescriptions[TEMP_WARNING] = "TEMP_WARNING: Approaching maximum temperature";
    statusDescriptions[TEMP_OUT_OF_RANGE] = "TEMP_OUT_OF_RANGE";
    statusDescriptions[CHARGE_RATE_WARNING] = "CHARGE_RATE_WARNING: Approaching maximum charge rate";
    statusDescriptions[CHARGE_RATE_OUT_OF_RANGE] = "CHARGE_RATE_OUT_OF_RANGE";
    return statusDescriptions;
}

// Function to get SOC status
StatusCode getSOCStatus(float soc) {
    if (soc < SOC_MIN || soc > SOC_MAX) {
        return SOC_OUT_OF_RANGE;
    }
    if (soc < SOC_MIN + SOC_WARNING_MIN_TOLERANCE) {
        return LOW_SOC_WARNING;
    } else if (soc > SOC_MAX - SOC_WARNING_MAX_TOLERANCE) {
        return HIGH_SOC_WARNING;
    }
    return NORMAL;
}

// Function to get temperature status
StatusCode getTemperatureStatus(float temp) {
    if (temp > TEMP_MAX) {
        return TEMP_OUT_OF_RANGE;
    }
    if (temp > TEMP_MAX - TEMP_WARNING_TOLERANCE) {
        return TEMP_WARNING;
    }
    return NORMAL;
}

// Function to get charge rate status
StatusCode getChargeRateStatus(float chargeRate) {
    if (chargeRate > CHARGE_RATE_MAX) {
        return CHARGE_RATE_OUT_OF_RANGE;
    }
    if (chargeRate > CHARGE_RATE_MAX - CHARGE_RATE_WARNING_TOLERANCE) {
        return CHARGE_RATE_WARNING;
    }
    return NORMAL;
}

// Main function to validate system
StatusCode validateSystem(float soc, float temp, float chargeRate) {
    StatusCode socStatus = getSOCStatus(soc);
    if (socStatus != NORMAL) return socStatus;

    StatusCode tempStatus = getTemperatureStatus(temp);
    if (tempStatus != NORMAL) return tempStatus;

    StatusCode chargeRateStatus = getChargeRateStatus(chargeRate);
    if (chargeRateStatus != NORMAL) return chargeRateStatus;

    return NORMAL;
}

// Function to check if the battery is OK
bool batteryIsOk(float soc, float temp, float chargeRate) {
    return validateSystem(soc, temp, chargeRate) == NORMAL;
}

// Function to get a descriptive string for StatusCode
std::string statusCodeToString(StatusCode status) {
    auto statusDescriptions = createStatusDescriptionMap();
    return statusDescriptions.at(status);
}

int main() {
    // Helper function to print status descriptions
    auto printStatus = [](float soc, float temp, float chargeRate) {
        StatusCode status = validateSystem(soc, temp, chargeRate);
        std::cout << "SOC: " << soc << ", Temp: " << temp << ", Charge Rate: " << chargeRate
                  << " -> Status: " << statusCodeToString(status) << std::endl;
        return status;
    };

    // Test cases with expected results
    StatusCode status1 = printStatus(25, 40, 0.7);
    assert(batteryIsOk(25, 40, 0.7) == true); // SOC and charge rate within range, temperature within range

    StatusCode status2 = printStatus(50, 85, 0);
    assert(batteryIsOk(50, 85, 0) == false); // Temperature out of range

    // Additional test cases
    StatusCode status3 = printStatus(22, 30, 0.5);   // Temperature within range, SOC within range, charge rate within range
    assert(batteryIsOk(22, 30, 0.5) == true);

    StatusCode status4 = printStatus(0, 20, 0.9);    // Temperature out of range, SOC within range, charge rate out of range
    assert(batteryIsOk(0, 20, 0.9) == false);

    StatusCode status6 = printStatus(35, 75, 0.85);  // Temperature within range, SOC within range, charge rate out of range
    assert(batteryIsOk(35, 75, 0.85) == false);

    // Testing edge cases
    StatusCode status7 = printStatus(20, 45, 0.8);    // Minimum SOC, maximum temperature within range, maximum charge rate within range
    assert(batteryIsOk(20, 45, 0.8) == false);      // SOC just at threshold, temperature just at threshold, charge rate within range

    StatusCode status8 = printStatus(80, 45, 0.8);    // Maximum SOC, maximum temperature within range, maximum charge rate within range
    assert(batteryIsOk(80, 45, 0.8) == false);      // SOC just at threshold, temperature within range, charge rate within range

    StatusCode status9 = printStatus(19, 30, 0.79);   // SOC just below minimum, temperature within range, charge rate within range
    assert(batteryIsOk(19, 30, 0.79) == false);     // SOC below threshold

    StatusCode status10 = printStatus(21, 46, 0.81);  // SOC just above minimum, temperature just above maximum, charge rate just above maximum
    assert(batteryIsOk(21, 46, 0.81) == false);     // SOC just above threshold, temperature out of range, charge rate out of range

    // Test cases with different combinations of tolerance thresholds
    StatusCode status11 = printStatus(25, 42, 0.76);  // SOC and charge rate within range, temperature within warning tolerance
    assert(batteryIsOk(25, 42, 0.76) == true);      // SOC and charge rate within range, temperature within warning tolerance

    StatusCode status12 = printStatus(24.5, 44, 0.77); // SOC within warning tolerance, temperature within range, charge rate within range
    assert(batteryIsOk(24.5, 44, 0.77) == false);    // SOC within warning tolerance, temperature within range, charge rate within range

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
