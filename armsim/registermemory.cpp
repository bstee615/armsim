#include "registermemory.h"
#include <QDebug>

address RegisterMemory::SPSR_Index(ProcessorMode mode)
{
    if (mode == User || mode == System) {
        qCritical() << "Registers: Undefined behavior: access SPSR in User or System mode.";
        return 0;
    }
    else {
        return SPSR_OFFSET + ((mode - 2) * 4);
    }
}

RegisterMemory::RegisterMemory(): Memory(GPR_OFFSET + GPR_BYTES * 8)
{

}

word RegisterMemory::getRegisterValue(ProcessorMode mode, byte index)
{
    if (index > 15) {
        qCritical() << "Out of range.";
        return 0;
    }

    word value = ReadWord(getRegisterAddress(mode, index));

    if (index == 15) {
        value += 8;
    }
    return value;
}

word RegisterMemory::getRegisterValue(byte index)
{
    return getRegisterValue(getProcessorMode(), index);
}

void RegisterMemory::setRegisterValue(ProcessorMode mode, byte index, word value)
{
    if (index > 15) {
        qCritical() << "Out of range.";
        return;
    }
    WriteWord(getRegisterAddress(mode, index), value);
}

void RegisterMemory::setRegisterValue(byte index, word value)
{
    setRegisterValue(getProcessorMode(), index, value);
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
    for (int i = 0; i < 7; i ++) {
        if (encodedProcessorMode((ProcessorMode)i) == rawMode) {
            return (ProcessorMode)i;
        }
    }

    qCritical() << "Registers: Undefined processor mode.";
    exit(1);
}

void RegisterMemory::processException(ProcessorMode nextMode, address jumpAddress)
{
    setSPSR(nextMode, getCPSR()); // set SPSR_<nextmode> to CPSR
    setRegisterValue(nextMode, 14, getRegisterValue(15) - 8); // Set PC to LR_<nextmode>
    setProcessorMode(nextMode);
    setIRQ(false); // Disable interrupts
    setRegisterValue(15, jumpAddress); // Jump to exception handler
}

void RegisterMemory::setProcessorMode(ProcessorMode nextMode)
{
    WriteWord(CPSR_OFFSET, (ReadWord(CPSR_OFFSET) & 0xFFFFFFE0) | encodedProcessorMode(nextMode)); // Set mode bits in CPSR
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
        return ReadWord(SPSR_Index(mode));
    }
}

void RegisterMemory::setSPSR(ProcessorMode mode, word data)
{
    if (mode == User || mode == System) {
        qCritical() << "Registers: Undefined behavior: access SPSR in User or System mode.";
        return;
    }
    else {
        WriteWord(SPSR_Index(mode), data);
    }
}

void RegisterMemory::setSPSR(word data)
{
    setSPSR(getProcessorMode(), data);
}

bool RegisterMemory::getIRQ()
{
    return Memory::ExtractBits(getCPSR(), 7, 7) != 0;
}

void RegisterMemory::setIRQ(bool enabled)
{
    word cpsr = getCPSR();
    if (enabled) {
        cpsr = cpsr & (~0x80);
    }
    else {
        cpsr = cpsr | 0x80;
    }
    setCPSR(cpsr);
}

word RegisterMemory::encodedProcessorMode(ProcessorMode mode)
{
    switch (mode) {
    case User:
        return 0b10000;
    case FIQ:
        return 0b10001;
    case IRQ:
        return 0b10010;
    case Supervisor:
        return 0b10011;
    case Abort:
        return 0b10111;
    case Undefined:
        return 0b11011;
    case System:
        return 0b11111;
    }
    qCritical() << "encodedProcessorMode:" << "Unrecognized processor mode" << QString::number((int)mode);
    exit(1);
}

const char *RegisterMemory::processorModeToString(ProcessorMode mode)
{
    switch (mode) {
    case User:
        return "USR";
    case FIQ:
        return "FIQ";
    case IRQ:
        return "IRQ";
    case Supervisor:
        return "SVC";
    case Abort:
        return "ABT";
    case Undefined:
        return "UND";
    case System:
        return "SYS";
    }
    qCritical() << "processorModeToString:" << "Unrecognized processor mode" << QString::number((int)mode);
    exit(1);
}
