#ifndef REGISTERMEMORY_H
#define REGISTERMEMORY_H

#include "memory.h"

// Define register offsets
#define CPSR_OFFSET 0
#define SPSR_OFFSET 4
#define SPSR_BYTES 4 * 6

#define GPR_OFFSET SPSR_OFFSET + SPSR_BYTES
#define IP_OFFSET GPR_OFFSET + (4 * 12)
#define SP_OFFSET GPR_OFFSET + (4 * 13)
#define LR_OFFSET GPR_OFFSET + (4 * 14)
#define PC_OFFSET GPR_OFFSET + (4 * 15)
#define GPR_BYTES 4 * 16

enum NZCFFlag {
    Negative = 31,
    Zero = 30,
    Carry = 29,
    Overflow = 28
};

enum ProcessorMode: unsigned char {
    User = 0,
    FIQ = 1,
    IRQ = 2,
    Supervisor = 3,
    Abort = 4,
    Undefined = 5,
    System = 6
};

class RegisterMemory : public Memory
{
    address SPSR_Index(ProcessorMode mode);

public:
    RegisterMemory();

    word getRegisterValue(ProcessorMode mode, byte index);
    word getRegisterValue(byte index);
    void setRegisterValue(ProcessorMode mode, byte index, word value);
    void setRegisterValue(byte index, word value);

    word getRegisterAddress(ProcessorMode mode, word index);
    ProcessorMode getProcessorMode();
    void processException(ProcessorMode nextMode, address jumpAddress);
    void setProcessorMode(ProcessorMode nextMode);
    word getCPSR();
    void setCPSR(word data);
    bool getNZCF(NZCFFlag whichFlag);
    void setNZCFFlag(NZCFFlag whichFlag, bool val);
    word getSPSR();
    void setSPSR(ProcessorMode mode, word data);
    void setSPSR(word data);

    bool getIRQ();
    void setIRQ(bool enabled);

    word encodedProcessorMode(ProcessorMode mode);
    const char *processorModeToString(ProcessorMode mode);
};

#endif // REGISTERMEMORY_H
