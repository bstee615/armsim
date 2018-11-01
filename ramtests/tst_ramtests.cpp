/* tst_ramtests.cpp
 * Unit tests for the RAM class.
 */

#include <QtTest>
#include "memory.h"

class RAMTests : public QObject
{
    Q_OBJECT

    const unsigned int bytes = 100;
    Memory ram;

public:
    RAMTests(){}
    ~RAMTests(){}

private slots:
    void initTestCase();
    void init();

    void ReadWord_Success();
    void ReadWord_FailsInvalidAddress();
    void ReadWord_FailsOutOfBounds();
    void ReadHalfWord_Success();
    void ReadHalfWord_FailsInvalidAddress();
    void ReadHalfWord_FailsOutOfBounds();
    void ReadByte_Success();

    void Checksum_Success();
    void Checksum_SuccessAfterInitialization();

    void WriteWord_Success();
    void WriteWord_FailsInvalidAddress();
    void WriteWord_FailsOutOfBounds();
    void WriteHalfWord_Success();
    void WriteHalfWord_FailsInvalidAddress();
    void WriteHalfWord_FailsOutOfBounds();
    void WriteByte_Success();

    void TestFlag_Success();
    void TestFlag_FailsOutOfBounds();
    void TestFlag_FailsInvalidBit();

    void SetFlag_Success();
    void SetFlag_FailsOutOfBounds();
    void SetFlag_FailsInvalidBit();

    void ExtractBits_Success();
    void ExtractBits_FromAll1s();
    void ExtractBits_FromAll0s();

    void ClearMemory_Success();
};

void RAMTests::initTestCase()
{
    ram = Memory(bytes);
}

void RAMTests::init()
{
    ram.clearMemory();
}

void RAMTests::ReadWord_Success()
{
    byte *memory = ram.getMemory();
    memory[12] = 0x00;
    memory[13] = 0xFF;
    memory[14] = 0x00;
    memory[15] = 0x00;

    word w = ram.ReadWord(12);
    word target = 0x0000FF00;
    Q_ASSERT(w == target);
}
void RAMTests::ReadWord_FailsInvalidAddress()
{
    byte *memory = ram.getMemory();
    memory[0] = 96;
    memory[1] = 96;
    memory[2] = 96;
    memory[3] = 96;
    Q_ASSERT(ram.ReadWord(1) == 0);
}
void RAMTests::ReadWord_FailsOutOfBounds()
{
    try {
        ram.ReadWord(bytes);
    }
    catch (OutOfBoundsException ex) {
        return;
    }
    Q_ASSERT(false);
}

void RAMTests::ReadHalfWord_Success()
{
    byte *memory = ram.getMemory();
    memory[12] = 0xFF;
    memory[13] = 0x00;

    halfword w = ram.ReadHalfWord(12);
    halfword target = 0x00FF;
    Q_ASSERT(w == target);
}
void RAMTests::ReadHalfWord_FailsInvalidAddress()
{
    byte *memory = ram.getMemory();
    memory[0] = 83;
    memory[1] = 83;
    Q_ASSERT(ram.ReadHalfWord(1) == 0);
}
void RAMTests::ReadHalfWord_FailsOutOfBounds()
{
    try {
        ram.ReadHalfWord(bytes);
    }
    catch (OutOfBoundsException ex) {
        return;
    }
    Q_ASSERT(false);
}

void RAMTests::ReadByte_Success()
{
    byte *memory = ram.getMemory();
    memory[12] = 01;

    byte w = ram.ReadByte(12);
    byte target = 01;
    Q_ASSERT(w == target);
}

void RAMTests::Checksum_Success()
{
    Memory ram = Memory(4);
    byte *memory = ram.getMemory();
    memory[0] = 0x01;
    memory[1] = 0x82;
    memory[2] = 0x03;
    memory[3] = 0x84;
    Q_ASSERT(ram.Checksum() == 268);
    ram = Memory(32768);
    memory = ram.getMemory();
    memory[0] = 0x01;
    memory[1] = 0x82;
    memory[2] = 0x03;
    memory[3] = 0x84;
    Q_ASSERT(ram.Checksum() == 536854790);
}

void RAMTests::Checksum_SuccessAfterInitialization()
{
    Memory ram = Memory(10);
    Q_ASSERT(ram.Checksum() == 1+2+3+4+5+6+7+8+9);
}

void RAMTests::WriteHalfWord_Success()
{
    ram.WriteHalfWord(10, 0xFF01); // binary 1111111100000001
    byte *memory = ram.getMemory();
    Q_ASSERT(memory[10] == 0x01);
    Q_ASSERT(memory[11] == 0xFF);
}
void RAMTests::WriteHalfWord_FailsInvalidAddress()
{
    ram.WriteHalfWord(11, 0xFFFF); // binary all 1's
    byte *memory = ram.getMemory();
    Q_ASSERT(memory[10] == 0);
    Q_ASSERT(memory[11] == 0);
}
void RAMTests::WriteHalfWord_FailsOutOfBounds()
{
    try {
        ram.ReadHalfWord(bytes);
    }
    catch (OutOfBoundsException ex) {
        return;
    }
    Q_ASSERT(false);
}

void RAMTests::WriteWord_Success()
{
    ram.WriteWord(8, (word)0x0000FF01); // binary 00000000000000001111111100000001
    byte *memory = ram.getMemory();
    Q_ASSERT(memory[8] == (word)0x01);
    Q_ASSERT(memory[9] == (word)0xFF);
    Q_ASSERT(memory[10] == (word)0);
    Q_ASSERT(memory[11] == (word)0);
}
void RAMTests::WriteWord_FailsInvalidAddress()
{
    ram.WriteWord(10, (word)4294967295); // binary all 1's
    ram.WriteWord(9, (word)4294967295); // binary all 1's
    byte *memory = ram.getMemory();
    Q_ASSERT(memory[8] == (word)0);
    Q_ASSERT(memory[9] == (word)0);
    Q_ASSERT(memory[10] == (word)0);
    Q_ASSERT(memory[11] == (word)0);
}
void RAMTests::WriteWord_FailsOutOfBounds()
{
    try {
        ram.ReadWord(bytes);
    }
    catch (OutOfBoundsException ex) {
        return;
    }
    Q_ASSERT(false);
}

void RAMTests::WriteByte_Success()
{
    ram.WriteByte(10, 123);
    byte *memory = ram.getMemory();
    Q_ASSERT(memory[10] == 123);
}

void RAMTests::TestFlag_Success()
{
    const address addr = 12;
    ram.WriteWord(addr, 0x000F0000);
    Q_ASSERT(ram.TestFlag(addr, 15) == false);
    Q_ASSERT(ram.TestFlag(addr, 16) == true);
    Q_ASSERT(ram.TestFlag(addr, 17) == true);
    Q_ASSERT(ram.TestFlag(addr, 18) == true);
    Q_ASSERT(ram.TestFlag(addr, 19) == true);
    Q_ASSERT(ram.TestFlag(addr, 20) == false);
}

void RAMTests::TestFlag_FailsOutOfBounds()
{
    try {
        ram.SetFlag(bytes+1, 0, true);
    }
    catch (OutOfBoundsException ex) {
        return;
    }
    Q_ASSERT(false);
}

void RAMTests::TestFlag_FailsInvalidBit()
{
    try {
        ram.SetFlag(0, 32, true);
    }
    catch (InvalidBitException ex) {
        return;
    }
    Q_ASSERT(false);
}

void RAMTests::SetFlag_Success()
{
    ram.SetFlag(12, 0, true);
    ram.SetFlag(12, 19, true);
    ram.SetFlag(12, 31, true);
    Q_ASSERT(ram.getMemory()[12] == 1);
    Q_ASSERT(ram.getMemory()[14] == 0b1000);
    Q_ASSERT(ram.getMemory()[15] == 0b10000000);

    ram.SetFlag(12, 19, false);
    Q_ASSERT(ram.getMemory()[14] == 0);
}

void RAMTests::SetFlag_FailsOutOfBounds()
{
    try {
        ram.SetFlag(bytes+1, 0, true);
    }
    catch (OutOfBoundsException ex) {
        return;
    }
    Q_ASSERT(false);
}

void RAMTests::SetFlag_FailsInvalidBit()
{
    try {
        ram.SetFlag(0, 32, true);
    }
    catch (InvalidBitException ex) {
        return;
    }
    Q_ASSERT(false);
}

void RAMTests::ExtractBits_Success()
{
    Q_ASSERT(Memory::ExtractBits(0x05, 1, 3) == 4);
}

void RAMTests::ExtractBits_FromAll1s()
{
    Q_ASSERT(Memory::ExtractBits(0xFFFFFFFF, 0, 15) == 0x0000FFFF);
}

void RAMTests::ExtractBits_FromAll0s()
{
    Q_ASSERT(Memory::ExtractBits(0, 0, 16) == 0);
}

void RAMTests::ClearMemory_Success()
{
    int cksum = ram.Checksum();
    ram.WriteWord(bytes/2, 0xFADE);
    Q_ASSERT(cksum != ram.Checksum());
    ram.clearMemory();
    Q_ASSERT(cksum == ram.Checksum());
}

QTEST_APPLESS_MAIN(RAMTests)

#include "tst_ramtests.moc"
