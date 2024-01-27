#include "BrytecBoard.h"

#include "CanBus.h"
#include "Fram.h"
#include "FramDeserializer.h"
#include "InputModuleRev2Defs.h"
#include "Usb.h"
#include "gpio.h"

namespace Brytec {

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
}

void BrytecBoard::shutdownAllPins()
{
}

float BrytecBoard::getPinValue(uint16_t index, IOTypes::Types type)
{
    return 0.0f;
}

float BrytecBoard::getPinVoltage(uint16_t index)
{
    return 0.0f;
}

float BrytecBoard::getPinCurrent(uint16_t index)
{
    return 0.0f;
}

void BrytecBoard::setPinValue(uint16_t index, IOTypes::Types type, float value)
{
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