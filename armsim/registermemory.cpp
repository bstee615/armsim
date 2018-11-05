#include "registermemory.h"
#include <QDebug>

word RegisterMemory::EncodedProcessorModes[8] = { 0x10, 0x11, 0x12, 0x00, 0x13, 0x17, 0x18, 0x1F };

address RegisterMemory::SPSR_Index()
{
    ProcessorMode mode = getProcessorMode();
    if (mode == User || mode == System) {
        qCritical() << "Registers: Undefined behavior: access SPSR in User or System mode.";
        return 0;
    }
    else {
        return SPSR_OFFSET + ((mode - 2) * 4);
    }
}

RegisterMemory::RegisterMemory(): Memory(GPR_OFFSET + GPR_BYTES * 7)
{
    setProcessorMode(User); // TODO: Fix the bandaid fix.
}

word RegisterMemory::getRegisterValue(byte index)
{
    if (index > 15) {
        qCritical() << "Out of range.";
        return 0;
    }

    ProcessorMode processorMode = getProcessorMode();
    word value = ReadWord(getRegisterAddress(processorMode, index));

    if (index == 15) {
        value += 8;
    }
    return value;
}

void RegisterMemory::setRegisterValue(byte index, word value)
{
    if (index > 15) {
        qCritical() << "Out of range.";
        return;
    }

    ProcessorMode processorMode = getProcessorMode();
    WriteWord(getRegisterAddress(processorMode, index), value);
}

word RegisterMemory::getRegisterAddress(ProcessorMode mode, word index)
{
    word offset = GPR_OFFSET;
    switch (index) {
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        if (mode == FIQ) {
            offset = GPR_OFFSET + (GPR_BYTES * mode);
        }
        break;
    case 13:
    case 14:
        offset = GPR_OFFSET + (GPR_BYTES * mode);
        break;
    }
    return offset + index*4;
}

ProcessorMode RegisterMemory::getProcessorMode()
{
    word cpsr_contents = ReadWord(CPSR_OFFSET);
    word rawMode = ExtractBits(cpsr_contents, 0, 4);
    for (int i = 0; i < 8; i ++) {
        if (EncodedProcessorModes[i] == rawMode) {
            return (ProcessorMode)i;
        }
    }

    qCritical() << "Registers: Undefined processor mode.";
    return Unknown;
}

void RegisterMemory::setProcessorMode(ProcessorMode mode)
{
    word cpsr_contents = ReadWord(CPSR_OFFSET);
    WriteWord(CPSR_OFFSET, (cpsr_contents & 0xFFFFFFE0) | EncodedProcessorModes[mode]);
}

word RegisterMemory::getCPSR()
{
    return ReadWord(CPSR_OFFSET);
}

void RegisterMemory::setCPSR(word data)
{
    WriteWord(CPSR_OFFSET, data);
}

bool RegisterMemory::getNZCF(NZCFFlag whichFlag)
{
    return TestFlag(CPSR_OFFSET, whichFlag);
}

void RegisterMemory::setNZCFFlag(NZCFFlag whichFlag, bool val)
{
    SetFlag(CPSR_OFFSET, whichFlag, val);
}

word RegisterMemory::getSPSR()
{
    ProcessorMode mode = getProcessorMode();
    if (mode == User || mode == System) {
        qCritical() << "Registers: Undefined behavior: access SPSR in User or System mode.";
        return 0;
    }
    else {
        return ReadWord(SPSR_Index());
    }
}

void RegisterMemory::setSPSR(word data)
{
    ProcessorMode mode = getProcessorMode();
    if (mode == User || mode == System) {
        qCritical() << "Registers: Undefined behavior: access SPSR in User or System mode.";
        return;
    }
    else {
        WriteWord(SPSR_Index(), data);
    }
}

bool RegisterMemory::getIRQ()
{
    return Memory::ExtractBits(getCPSR(), 7, 7) != 0;
}
