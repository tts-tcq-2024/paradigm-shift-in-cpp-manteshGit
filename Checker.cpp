#include "batteryStatus.h"
#include <cassert>
#include <iostream>

void testcases() {
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
}

int main() {
    testcases();
    return 0;
}
