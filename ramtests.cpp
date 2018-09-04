
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
    static void ReadWord_FailsOutOfBounds(RAM ram)
    {
        try {
            ram.ReadWord(bytes);
        }
        catch (OutOfBoundsException ex) {
            return;
        }
        Q_ASSERT(false);
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
    static void ReadHalfWord_FailsOutOfBounds(RAM ram)
    {
        try {
            ram.ReadHalfWord(bytes);
        }
        catch (OutOfBoundsException ex) {
            return;
        }
        Q_ASSERT(false);
    }

    static void ReadByte_Success(RAM ram)
    {
        byte *memory = ram.getMemory();
        memory[12] = 01;

        byte w = ram.ReadByte(12);
        byte target = 01;
        Q_ASSERT(w == target);
    }

    static void Checksum_Success()
    {
        RAM ram = RAM(2);
        byte *memory = ram.getMemory();
        memory[0] = 1;
        memory[1] = 1;
        Q_ASSERT(ram.Checksum() == 1);
        memory[0] = 1;
        memory[1] = 0;
        Q_ASSERT(ram.Checksum() == 2);
    }

    static void Checksum_SuccessAfterInitialization()
    {
        RAM ram = RAM(10);
        Q_ASSERT(ram.Checksum() == 1+2+3+4+5+6+7+8+9);
    }

    static void WriteHalfWord_Success(RAM ram)
    {
        ram.WriteHalfWord(10, (halfword)65281); // binary 1111111100000001
        byte *memory = ram.getMemory();
        Q_ASSERT(memory[10] == (halfword)255);
        Q_ASSERT(memory[11] == (halfword)1);
    }
    static void WriteHalfWord_FailsInvalidAddress(RAM ram)
    {
        ram.WriteHalfWord(11, (halfword)65535); // binary all 1's
        byte *memory = ram.getMemory();
        Q_ASSERT(memory[10] == (halfword)0);
        Q_ASSERT(memory[11] == (halfword)0);
    }
    static void WriteHalfWord_FailsOutOfBounds(RAM ram)
    {
        try {
            ram.ReadHalfWord(bytes);
        }
        catch (OutOfBoundsException ex) {
            return;
        }
        Q_ASSERT(false);
    }

    static void WriteWord_Success(RAM ram)
    {
        ram.WriteWord(8, (word)65281); // binary 00000000000000001111111100000001
        byte *memory = ram.getMemory();
        Q_ASSERT(memory[8] == (word)0);
        Q_ASSERT(memory[9] == (word)0);
        Q_ASSERT(memory[10] == (word)255);
        Q_ASSERT(memory[11] == (word)1);
    }
    static void WriteWord_FailsInvalidAddress(RAM ram)
    {
        ram.WriteWord(10, (word)4294967295); // binary all 1's
        ram.WriteWord(9, (word)4294967295); // binary all 1's
        byte *memory = ram.getMemory();
        Q_ASSERT(memory[8] == (word)0);
        Q_ASSERT(memory[9] == (word)0);
        Q_ASSERT(memory[10] == (word)0);
        Q_ASSERT(memory[11] == (word)0);
    }
    static void WriteWord_FailsOutOfBounds(RAM ram)
    {
        try {
            ram.ReadWord(bytes);
        }
        catch (OutOfBoundsException ex) {
            return;
        }
        Q_ASSERT(false);
    }

    static void WriteByte_Success(RAM ram)
    {
        ram.WriteByte(10, 123);
        byte *memory = ram.getMemory();
        Q_ASSERT(memory[10] == 123);
    }

public:
    static void RunAllTests()
    {
        RAM ram = RAM(bytes);

        ReadWord_Success(ram);
        ReadWord_FailsInvalidAddress(ram);
        ReadWord_FailsOutOfBounds(ram);
        ReadHalfWord_Success(ram);
        ReadHalfWord_FailsInvalidAddress(ram);
        ReadHalfWord_FailsOutOfBounds(ram);
        ReadByte_Success(ram);

        Checksum_Success();
        Checksum_SuccessAfterInitialization();

        WriteWord_Success(ram);
        WriteWord_FailsInvalidAddress(ram);
        WriteWord_FailsOutOfBounds(ram);
        WriteHalfWord_Success(ram);
        WriteHalfWord_FailsInvalidAddress(ram);
        WriteHalfWord_FailsOutOfBounds(ram);
        WriteByte_Success(ram);
    }
};
