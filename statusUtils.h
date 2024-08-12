#ifndef STATUSUTILS_H
#define STATUSUTILS_H

#include "statusCodes.h"
#include <string>
#include <tuple>
#include <map>

std::map<StatusCode, std::string> createStatusDescriptionMap();
std::string statusCodeToString(StatusCode status);
void printStatus(float soc, float temp, float chargeRate, StatusCode socStatus, StatusCode tempStatus, StatusCode chargeRateStatus);


#endif // STATUSUTILS_H
