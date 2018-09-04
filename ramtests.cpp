
#include "ram.h"
#include <QDebug>

static const unsigned long int bytes = 100;

class RAMTests
{
    static void ReadWord_Success(RAM ram)
    {
        byte *memory = ram.getMemory();
        memory[12] = 01;
        memory[13] = 23;
        memory[14] = 45;
        memory[15] = 67;

        word w = ram.ReadWord(12);
        word target = 67<<12 | 45<<8 | 23<<4 | 1<<0; // Little-Endian
        Q_ASSERT(w == target);
    }
    static void ReadWord_FailsInvalidAddress(RAM ram)
    {
        byte *memory = ram.getMemory();
        memory[0] = 96;
        memory[1] = 96;
        memory[2] = 96;
        memory[3] = 96;
        Q_ASSERT(ram.ReadWord(1) == 0);
    }

    static void ReadHalfWord_Success(RAM ram)
    {
        byte *memory = ram.getMemory();
        memory[12] = 01;
        memory[13] = 23;

        halfword w = ram.ReadHalfWord(12);
        halfword target = 23<<4 | 1<<0; // Little-Endian
        Q_ASSERT(w == target);
    }
    static void ReadHalfWord_FailsInvalidAddress(RAM ram)
    {
        byte *memory = ram.getMemory();
        memory[0] = 83;
        memory[1] = 83;
        Q_ASSERT(ram.ReadHalfWord(1) == 0);
    }

    static void ReadByte_Success(RAM ram)
    {
        byte *memory = ram.getMemory();
        memory[12] = 01;

        byte w = ram.ReadByte(12);
        byte target = 01;
        Q_ASSERT(w == target);
    }

public:
    static void RunAllTests()
    {
        RAM ram = RAM(bytes);
        ReadWord_Success(ram);
        ReadWord_FailsInvalidAddress(ram);
        ReadHalfWord_Success(ram);
        ReadHalfWord_FailsInvalidAddress(ram);
        ReadByte_Success(ram);
    }
};
