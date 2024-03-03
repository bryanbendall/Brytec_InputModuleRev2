#pragma once

#include <stdint.h>

class BoardHardware {

public:
    static bool getIgntionPowerState();
    static void setSpiTLE94112();
    static void setSpiL9966();
};