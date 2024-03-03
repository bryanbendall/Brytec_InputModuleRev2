#include "BrytecBoard.h"

#include "BoardHardware.h"
#include "BoardPinInput.h"
#include "CanBus.h"
#include "Fram.h"
#include "FramDeserializer.h"
#include "InputModuleRev2Defs.h"
#include "L9966Input.h"
#include "TLE94112.h"
#include "Usb.h"
#include "gpio.h"

namespace Brytec {

// Inputs
using in1 = BoardPinInput<L9966Input<5>>;
using in2 = BoardPinInput<L9966Input<6>>;
using in3 = BoardPinInput<L9966Input<7>>;
using in4 = BoardPinInput<L9966Input<8>>;
using in5 = BoardPinInput<L9966Input<9>>;
using in6 = BoardPinInput<L9966Input<10>>;
using in7 = BoardPinInput<L9966Input<11>>;
using in8 = BoardPinInput<L9966Input<12>>;
using in9 = BoardPinInput<L9966Input<13>>;
using in10 = BoardPinInput<L9966Input<14>>;
using in11 = BoardPinInput<L9966Input<15>>;
using in12 = BoardPinInput<L9966Input<1>>;
using in13 = BoardPinInput<L9966Input<2>>;
using in14 = BoardPinInput<L9966Input<3>>;
using in15 = BoardPinInput<L9966Input<4>>;

FramDeserializer deserializer;

BinaryDeserializer* BrytecBoard::getDeserializer()
{
    FramDeserializer des;
    deserializer = des;
    return &deserializer;
}

void BrytecBoard::error(EBrytecErrors error)
{
    switch (error) {
    case EBrytecErrors::ModuleHeader:
        printf("Module header is wrong\n");
        break;
    case EBrytecErrors::NodeGroupHeader:
        printf("Node Group header is wrong\n");
        break;
    case EBrytecErrors::ModuleNotEnabled:
        printf("This module is not enabled\n");
        break;
    case EBrytecErrors::AddNodeFailed:
        printf("Failed to add node\n");
        break;
    case EBrytecErrors::NodeVectorOutOfSpace:
        printf("Node Vector out of space\n");
        break;
    case EBrytecErrors::FailedToCreateNode:
        printf("Failed to create node\n");
        break;
    case EBrytecErrors::NodeIndexOutOfBounds:
        printf("Node index out of bounds\n");
        break;
    case EBrytecErrors::BadAlloc:
        printf("Node group allocation failed\n");
        break;
    case EBrytecErrors::CanBufferFull:
        printf("Can Buffer Full\n");
        break;

    default:
        printf("Unknown Error\n");
        break;
    }
}

void BrytecBoard::setupCan(uint8_t index, CanSpeed::Types speed)
{
    CanBus::start(index, speed);
}

void BrytecBoard::setupPin(uint16_t index, IOTypes::Types type)
{
    BoardHardware::setSpiL9966();

    switch (index) {
    // Inputs
    case BT_PIN_Pin_10:
        in15::setupType(type);
        break;
    case BT_PIN_Pin_11:
        in14::setupType(type);
        break;
    case BT_PIN_Pin_12:
        in13::setupType(type);
        break;
    case BT_PIN_Pin_18:
        in12::setupType(type);
        break;
    case BT_PIN_Pin_19:
        in11::setupType(type);
        break;
    case BT_PIN_Pin_20:
        in10::setupType(type);
        break;
    case BT_PIN_Pin_21:
        in4::setupType(type);
        break;
    case BT_PIN_Pin_22:
        in6::setupType(type);
        break;
    case BT_PIN_Pin_26:
        in9::setupType(type);
        break;
    case BT_PIN_Pin_27:
        in1::setupType(type);
        break;
    case BT_PIN_Pin_28:
        in2::setupType(type);
        break;
    case BT_PIN_Pin_29:
        in3::setupType(type);
        break;
    case BT_PIN_Pin_30:
        in5::setupType(type);
        break;
    case BT_PIN_Pin_31:
        in7::setupType(type);
        break;
    case BT_PIN_Pin_32:
        in8::setupType(type);
        break;

    default:
        break;
    }
}

void BrytecBoard::shutdownAllPins()
{
    HAL_GPIO_WritePin(User_Led_GPIO_Port, User_Led_Pin, GPIO_PIN_RESET);

    BoardHardware::setSpiL9966();
    L9966::softwareReset();
    L9966::init(&hspi2);

    BoardHardware::setSpiTLE94112();
    TLE94112::setAllOff();
}

float BrytecBoard::getPinValue(uint16_t index, IOTypes::Types type)
{
    if (!BoardHardware::getIgntionPowerState())
        return 0.0f;

    BoardHardware::setSpiL9966();

    switch (index) {
        // Inputs
    case BT_PIN_Pin_10:
        return in15::getValue(type);
    case BT_PIN_Pin_11:
        return in14::getValue(type);
    case BT_PIN_Pin_12:
        return in13::getValue(type);
    case BT_PIN_Pin_18:
        return in12::getValue(type);
    case BT_PIN_Pin_19:
        return in11::getValue(type);
    case BT_PIN_Pin_20:
        return in10::getValue(type);
    case BT_PIN_Pin_21:
        return in4::getValue(type);
    case BT_PIN_Pin_22:
        return in6::getValue(type);
    case BT_PIN_Pin_26:
        return in9::getValue(type);
    case BT_PIN_Pin_27:
        return in1::getValue(type);
    case BT_PIN_Pin_28:
        return in2::getValue(type);
    case BT_PIN_Pin_29:
        return in3::getValue(type);
    case BT_PIN_Pin_30:
        return in5::getValue(type);
    case BT_PIN_Pin_31:
        return in7::getValue(type);
    case BT_PIN_Pin_32:
        return in8::getValue(type);

    default:
        break;
    }

    return 0.0f;
}

float BrytecBoard::getPinVoltage(uint16_t index)
{
    // Not used
    return 0.0f;
}

float BrytecBoard::getPinCurrent(uint16_t index)
{
    BoardHardware::setSpiTLE94112();

    bool overCurrent = false;

    switch (index) {
    case BT_PIN_Pin_6:
        overCurrent = TLE94112::isOverCurrent(5);
        break;
    case BT_PIN_Pin_7:
        overCurrent = TLE94112::isOverCurrent(9);
        break;
    case BT_PIN_Pin_8:
        overCurrent = TLE94112::isOverCurrent(4);
        break;
    case BT_PIN_Pin_9:
        overCurrent = TLE94112::isOverCurrent(3);
        break;
    case BT_PIN_Pin_14:
        overCurrent = TLE94112::isOverCurrent(7);
        break;
    case BT_PIN_Pin_15:
        overCurrent = TLE94112::isOverCurrent(6);
        break;
    case BT_PIN_Pin_16:
        overCurrent = TLE94112::isOverCurrent(10);
        break;
    case BT_PIN_Pin_17:
        overCurrent = TLE94112::isOverCurrent(11);
        break;
    case BT_PIN_Pin_23:
        overCurrent = TLE94112::isOverCurrent(12);
        break;
    case BT_PIN_Pin_24:
        overCurrent = TLE94112::isOverCurrent(2);
        break;
    case BT_PIN_Pin_25:
        overCurrent = TLE94112::isOverCurrent(8);
        break;

    default:
        break;
    }

    if (overCurrent)
        return 99.0f;
    else
        return 0.0f;
}

void BrytecBoard::setPinValue(uint16_t index, IOTypes::Types type, float value)
{
    if (index == BT_PIN_Onboard_LED) {
        HAL_GPIO_WritePin(User_Led_GPIO_Port, User_Led_Pin, (GPIO_PinState)(value > 0.001f));
        return;
    }

    BoardHardware::setSpiTLE94112();

    TLE94112::OutputDrive drive = TLE94112::OutputDrive::Off;
    if (value > 0.001f) {
        switch (type) {
        case IOTypes::Types::Output_Ground:
            drive = TLE94112::OutputDrive::LowSide;
            break;
        case IOTypes::Types::Output_Batt:
            drive = TLE94112::OutputDrive::HighSide;
            break;
        default:
            break;
        }
    }

    if (!BoardHardware::getIgntionPowerState())
        drive = TLE94112::OutputDrive::Off;

    switch (index) {
    case BT_PIN_Pin_6:
        TLE94112::setOutput(5, drive);
        break;
    case BT_PIN_Pin_7:
        TLE94112::setOutput(9, drive);
        break;
    case BT_PIN_Pin_8:
        TLE94112::setOutput(4, drive);
        break;
    case BT_PIN_Pin_9:
        TLE94112::setOutput(3, drive);
        break;
    case BT_PIN_Pin_14:
        TLE94112::setOutput(7, drive);
        break;
    case BT_PIN_Pin_15:
        TLE94112::setOutput(6, drive);
        break;
    case BT_PIN_Pin_16:
        TLE94112::setOutput(10, drive);
        break;
    case BT_PIN_Pin_17:
        TLE94112::setOutput(11, drive);
        break;
    case BT_PIN_Pin_23:
        TLE94112::setOutput(12, drive);
        break;
    case BT_PIN_Pin_24:
        TLE94112::setOutput(2, drive);
        break;
    case BT_PIN_Pin_25:
        TLE94112::setOutput(8, drive);
        break;

    default:
        break;
    }
}

void BrytecBoard::sendCan(uint8_t index, const CanFrame& frame)
{
    CanBus::send(index, frame);
}

void BrytecBoard::sendBrytecCanUsb(const CanFrame& frame)
{
    Brytec::UsbPacket packet;
    packet.set<Brytec::CanFrame>(frame);
    Usb::send(packet);
}

void BrytecBoard::ReserveConfigSize(uint16_t size)
{
    Fram::write(0, (uint8_t*)&size, 2);
}

void BrytecBoard::updateConfig(uint8_t* data, uint32_t size, uint32_t offset)
{
    // Add room for storing the size
    Fram::write(offset + 2, data, size);
}

uint32_t BrytecBoard::getTemplateSize()
{
    return sizeof(moduleTemplate);
}

void BrytecBoard::getTemplateData(uint8_t* dest, uint32_t offset, uint32_t length)
{
    if (offset > sizeof(moduleTemplate))
        return;

    memcpy(dest, &moduleTemplate[offset], length);
}

uint32_t BrytecBoard::getConfigSize()
{
    uint16_t dataSize;
    Fram::read(0, (uint8_t*)&dataSize, 2);
    return dataSize;
}

void BrytecBoard::getConfigData(uint8_t* dest, uint32_t offset, uint32_t length)
{
    Fram::read(offset + 2, dest, length);
}
}