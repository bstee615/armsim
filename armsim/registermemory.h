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
    System = 1,
    Supervisor = 2,
    Monitor = 3,
    Abort = 4,
    Undefined = 5,
    FIQ = 6,
    IRQ = 7,
    Unknown = 8
};

static char const * ProcessorModeToString[] = {
    "User", "System", "Supervisor", "Monitor", "Abort", "Undefined", "FIQ", "IRQ", "Unknown processor mode."
};

class RegisterMemory : public Memory
{
    static word EncodedProcessorModes[8];

    address SPSR_Index();

public:
    RegisterMemory();

    word getRegisterValue(byte index);
    void setRegisterValue(byte index, word value);

    word getRegisterAddress(ProcessorMode mode, word index);
    ProcessorMode getProcessorMode();
    void setProcessorMode(ProcessorMode mode);
    word getCPSR();
    void setCPSR(word data);
    bool getNZCF(NZCFFlag whichFlag);
    void setNZCFFlag(NZCFFlag whichFlag, bool val);
    word getSPSR();
    void setSPSR(word data);

    bool getIRQ();
};

#endif // REGISTERMEMORY_H
