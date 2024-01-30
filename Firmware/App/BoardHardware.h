#pragma once

#include <stdint.h>

class BoardHardware {

public:
    static void setSpiMemory();
    static void setSpiL9966();

    static bool getIgntionPowerState();
};