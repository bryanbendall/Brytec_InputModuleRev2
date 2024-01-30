#include "InputModuleRev2Defs.h"
#include "fdcan.h"
#include <stdint.h>

namespace CanBusDefs {

FDCAN_HandleTypeDef* getCanBus(uint8_t index)
{
    switch (index) {
    case BT_CAN_Pin_4_Pin_3:
        return &hfdcan1;
    case BT_CAN_Pin_2_Pin_1:
        return &hfdcan2;
    }

    return nullptr;
}

uint8_t getCanBusIndex(FDCAN_HandleTypeDef* bus)
{
    if (bus == &hfdcan1)
        return BT_CAN_Pin_4_Pin_3;

    if (bus == &hfdcan2)
        return BT_CAN_Pin_2_Pin_1;

    return UINT8_MAX;
}

}