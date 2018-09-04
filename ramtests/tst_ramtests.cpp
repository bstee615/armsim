#include <QtTest>
#include "ram.h"

class RAMTests : public QObject
{
    Q_OBJECT

    const unsigned int bytes = 100;
    RAM ram;

public:
    RAMTests(){}
    ~RAMTests(){}

private slots:
    void initTestCase();
    void cleanupTestCase();

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

    void SetFlag_Success();
};

void RAMTests::initTestCase()
{
    ram = RAM(bytes);
}

void RAMTests::cleanupTestCase()
{

}

void RAMTests::ReadWord_Success()
{
    ram.clearMemory();
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
    ram.clearMemory();
    byte *memory = ram.getMemory();
    memory[0] = 96;
    memory[1] = 96;
    memory[2] = 96;
    memory[3] = 96;
    Q_ASSERT(ram.ReadWord(1) == 0);
}
void RAMTests::ReadWord_FailsOutOfBounds()
{
    ram.clearMemory();
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
    ram.clearMemory();
    byte *memory = ram.getMemory();
    memory[12] = 0xFF;
    memory[13] = 0x00;

    halfword w = ram.ReadHalfWord(12);
    halfword target = 0x00FF;
    Q_ASSERT(w == target);
}
void RAMTests::ReadHalfWord_FailsInvalidAddress()
{
    ram.clearMemory();
    byte *memory = ram.getMemory();
    memory[0] = 83;
    memory[1] = 83;
    Q_ASSERT(ram.ReadHalfWord(1) == 0);
}
void RAMTests::ReadHalfWord_FailsOutOfBounds()
{
    ram.clearMemory();
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
    ram.clearMemory();
    byte *memory = ram.getMemory();
    memory[12] = 01;

    byte w = ram.ReadByte(12);
    byte target = 01;
    Q_ASSERT(w == target);
}

void RAMTests::Checksum_Success()
{
    ram.clearMemory();
    RAM ram = RAM(2);
    byte *memory = ram.getMemory();
    memory[0] = 1;
    memory[1] = 1;
    Q_ASSERT(ram.Checksum() == 1);
    memory[0] = 1;
    memory[1] = 0;
    Q_ASSERT(ram.Checksum() == 2);
}

void RAMTests::Checksum_SuccessAfterInitialization()
{
    ram.clearMemory();
    RAM ram = RAM(10);
    Q_ASSERT(ram.Checksum() == 1+2+3+4+5+6+7+8+9);
}

void RAMTests::WriteHalfWord_Success()
{
    ram.clearMemory();
    ram.WriteHalfWord(10, 0xFF01); // binary 1111111100000001
    byte *memory = ram.getMemory();
    Q_ASSERT(memory[10] == 0x01);
    Q_ASSERT(memory[11] == 0xFF);
}
void RAMTests::WriteHalfWord_FailsInvalidAddress()
{
    ram.clearMemory();
    ram.WriteHalfWord(11, 0xFFFF); // binary all 1's
    byte *memory = ram.getMemory();
    Q_ASSERT(memory[10] == 0);
    Q_ASSERT(memory[11] == 0);
}
void RAMTests::WriteHalfWord_FailsOutOfBounds()
{
    ram.clearMemory();
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
    ram.clearMemory();
    ram.WriteWord(8, (word)0x0000FF01); // binary 00000000000000001111111100000001
    byte *memory = ram.getMemory();
    Q_ASSERT(memory[8] == (word)0x01);
    Q_ASSERT(memory[9] == (word)0xFF);
    Q_ASSERT(memory[10] == (word)0);
    Q_ASSERT(memory[11] == (word)0);
}
void RAMTests::WriteWord_FailsInvalidAddress()
{
    ram.clearMemory();
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
    ram.clearMemory();
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
    ram.clearMemory();
    ram.WriteByte(10, 123);
    byte *memory = ram.getMemory();
    Q_ASSERT(memory[10] == 123);
}

void RAMTests::TestFlag_Success()
{
    ram.clearMemory();
    const address addr = 12;
    ram.WriteWord(addr, 0x000F0000);
    Q_ASSERT(ram.TestFlag(addr, 15) == false);
    Q_ASSERT(ram.TestFlag(addr, 16) == true);
    Q_ASSERT(ram.TestFlag(addr, 17) == true);
    Q_ASSERT(ram.TestFlag(addr, 18) == true);
    Q_ASSERT(ram.TestFlag(addr, 19) == true);
    Q_ASSERT(ram.TestFlag(addr, 20) == false);
}

void RAMTests::SetFlag_Success()
{
    ram.clearMemory();
    ram.SetFlag(12, 19, true);
    Q_ASSERT(ram.getMemory()[14] == 0b1000);
}

QTEST_APPLESS_MAIN(RAMTests)

#include "tst_ramtests.moc"
