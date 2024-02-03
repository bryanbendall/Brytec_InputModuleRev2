#include "BoardHardware.h"

#include "Stm32Output.h"
#include <stdio.h>

bool BoardHardware::getIgntionPowerState()
{
    return HAL_GPIO_ReadPin(PowerSwitchStatus_GPIO_Port, PowerSwitchStatus_Pin);
}