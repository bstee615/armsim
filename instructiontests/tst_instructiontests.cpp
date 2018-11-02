#include <QtTest>

#include "cpu.h"
#include "memory.h"
#include "instructions/dataprocessinginstruction.h"
#include "instructions/mulinstruction.h"

class InstructionTests : public QObject
{
    Q_OBJECT

    CPU *cpu;

    void assert_Instruction(word encodedInstruction, QString expectedDisassembly, byte destinationRegister, word expectedValue);
    void assert_Instruction(word encodedInstruction, QString expectedDisassembly, byte destinationRegister, word expectedValue, address destinationAddress, word expectedMemoryValue);

    void assert_cmp(word rNValue, word Operand2Value, byte expectedNZCF);
    void assert_cmn(word rNValue, word Operand2Value, byte expectedNZCF);

public:
    InstructionTests();
    ~InstructionTests();

private slots:
    void init();
    void cleanup();
    void mov();
    void movWithBigConstant();
    void movWithImmediateShiftedRegister();
    void movWithRegisterShiftedRegister();
    void mvn();
    void add();
    void addToSelf();
    void sub();
    void rsb();
    void _and();
    void orr();
    void eor();
    void bic();
    void mul();

    void cmp_flags();
    void cmn_flags();

    void b();
    void bl();

    void ldr();
    void str();
    void ldrWithImmediateOffset();
    void strWithImmediateOffset();
    void ldrWithRegisterOffset();
    void strWithRegisterOffset();

    void pushpopWithoutWriteback();
    void pushpopWithWriteback();
};

void InstructionTests::assert_Instruction(word encodedInstruction, QString expectedDisassembly, byte destinationRegister, word expectedValue)
{
    Instruction *instr = cpu->decode(encodedInstruction);
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), expectedDisassembly) == 0);

    instr->execute();
    Q_ASSERT(cpu->getGeneralRegister(destinationRegister) == expectedValue);
}

void InstructionTests::assert_cmp(word rNValue, word Operand2Value, byte expectedNZCF)
{
    cpu->setGeneralRegister(1, rNValue);
    cpu->setGeneralRegister(2, Operand2Value);
    assert_Instruction(0xe1510002, QString("cmp r1, r2"), 1, rNValue);
    qDebug() << rNValue << Operand2Value << cpu->getNZCF();
    Q_ASSERT(cpu->getNZCF() == expectedNZCF);
}

void InstructionTests::assert_cmn(word rNValue, word Operand2Value, byte expectedNZCF)
{
    cpu->setGeneralRegister(1, rNValue);
    cpu->setGeneralRegister(2, Operand2Value);
    assert_Instruction(0xe1710002, QString("cmn r1, r2"), 1, rNValue);
    qDebug() << cpu->getNZCF();
    Q_ASSERT(cpu->getNZCF() == expectedNZCF);
}

InstructionTests::InstructionTests(): cpu(new CPU(new Memory(32768)))
{

}

InstructionTests::~InstructionTests()
{
    delete cpu;
}

void InstructionTests::init()
{
    cpu->setGeneralRegister(13, 0x7000);
}

void InstructionTests::cleanup()
{
    cpu->getRegisters()->clearMemory();
    cpu->getRAM()->clearMemory();
}

void InstructionTests::mov()
{
    assert_Instruction(0xe3a02030, QString("mov r2, #48"), 2, 48);
}

void InstructionTests::movWithBigConstant()
{
    assert_Instruction(0xe3a00fb5, QString("mov r0, #724"), 0, 724);
}

void InstructionTests::movWithImmediateShiftedRegister()
{
    cpu->setGeneralRegister(1, 0xa1000000);
    assert_Instruction(0xe1a02141, QString("mov r2, r1, asr #2"), 2, 0xe8400000);
}

void InstructionTests::movWithRegisterShiftedRegister()
{
    cpu->setGeneralRegister(8, 0xa1000000);
    cpu->setGeneralRegister(10, 0x00000005);
    assert_Instruction(0xe1a06a38, QString("mov r6, r8, lsr r10"), 6, 0x05080000);
}

void InstructionTests::mvn()
{
    assert_Instruction(0xe3e07fb5, QString("mvn r7, #724"), 7, 0xfffffd2b);
}

void InstructionTests::add()
{
    cpu->setGeneralRegister(5, 0x000dabba);
    assert_Instruction(0xe2852019, QString("add r2, r5, #25"), 2, 0x000dabba + 25);
}

void InstructionTests::addToSelf()
{
    cpu->setGeneralRegister(5, 0x0baddeed);
    assert_Instruction(0xe285500F, QString("add r5, r5, #15"), 5, 0x0baddeed + 15);
}

void InstructionTests::sub()
{
    cpu->setGeneralRegister(7, 0xfaded000);
    cpu->setGeneralRegister(6, 0x00bedfab);
    assert_Instruction(0xe0465007, QString("sub r5, r6, r7"), 5, 0x00bedfab - 0xfaded000);
}

void InstructionTests::rsb()
{
    cpu->setGeneralRegister(1, 0xdeadbeef);
    cpu->setGeneralRegister(4, 0xbadd000d);
    assert_Instruction(0xe0612604, QString("rsb r2, r1, r4, lsl #12"), 2, 0xd000d000 - 0xdeadbeef);
}

void InstructionTests::_and()
{
    cpu->setGeneralRegister(0, 0xcafebabe);
    assert_Instruction(0xe200101d, QString("and r1, r0, #29"), 1, 28);
}

void InstructionTests::orr()
{
    cpu->setGeneralRegister(6, 0xfeedbeef);
    assert_Instruction(0xe3861a04, QString("orr r1, r6, #16384"), 1, 0xfeedfeef);
}

void InstructionTests::eor()
{
    cpu->setGeneralRegister(3, 0x20);
    assert_Instruction(0xe22340a0, QString("eor r4, r3, #160"), 4, 0x00000080);
}

void InstructionTests::bic()
{
    cpu->setGeneralRegister(0, 0xcafebabe);
    assert_Instruction(0xe3c01015, QString("bic r1, r0, #21"), 1, 0xcafebaaa);
}

void InstructionTests::mul()
{
    cpu->setGeneralRegister(1, 0xa1000000);
    cpu->setGeneralRegister(2, 0x00001050);
    assert_Instruction(0xe0050291, QString("mul r5, r1, r2"), 5, 0x50000000);
}

void InstructionTests::cmp_flags()
{
    assert_cmp(1, 2, 0b1000); // Negative
    assert_cmp(2, 1, 0b0010);
    assert_cmp(1, 1, 0b0110); // Zero
    assert_cmp(-5, -5, 0b0110); // Zero
    assert_cmp(0, 1, 0b1000); // Carry
}

void InstructionTests::cmn_flags()
{
    assert_cmn(1, 2, 0b0000); // Normal case
    assert_cmn(0x7FFFFFFF, 0x1, 0b1001); // Overflow
    assert_cmn(-4, 4, 0b0100); // Zero
}

void InstructionTests::b()
{
    assert_Instruction(0xea000001, QString("b #4"), 15, 8 + 4);
}

void InstructionTests::bl()
{
    assert_Instruction(0xeb000008, QString("bl #32"), 14, 4);
}

void InstructionTests::ldr()
{
    cpu->setGeneralRegister(2, 0x100);
    cpu->getRAM()->WriteWord(0x100, 0x12345678);
    assert_Instruction(0xe5925000, QString("ldr r5, [r2]"), 5, 0x12345678);
}

void InstructionTests::str()
{
    cpu->setGeneralRegister(1, 0xd000000d);
    cpu->setGeneralRegister(2, 0x100);
    assert_Instruction(0xe5821000, QString("str r1, [r2]"), 1, 0xd000000d);
    Q_ASSERT(cpu->getRAM()->ReadWord(0x100) == 0xd000000d);
}

void InstructionTests::ldrWithImmediateOffset()
{
    cpu->setGeneralRegister(2, 0x104);
    cpu->getRAM()->WriteWord(0x100, 0x10203040);
    assert_Instruction(0xe5126004, QString("ldr r6, [r2, -#4]"), 6, 0x10203040);
}

void InstructionTests::strWithImmediateOffset()
{
    cpu->setGeneralRegister(1, 0xd0d0dead);
    cpu->setGeneralRegister(5, 0x10c);
    assert_Instruction(0xe505100c, QString("str r1, [r5, -#12]"), 1, 0xd0d0dead);
    Q_ASSERT(cpu->getRAM()->ReadWord(0x100) == 0xd0d0dead);
}

void InstructionTests::ldrWithRegisterOffset()
{
    cpu->setGeneralRegister(2, 0x050);
    cpu->setGeneralRegister(4, 0x0b0);
    cpu->getRAM()->WriteWord(0x100, 0xdadadada);
    assert_Instruction(0xe7928004, QString("ldr r8, [r2, r4]"), 8, 0xdadadada);
    assert_Instruction(0xe7b28004, QString("ldr r8, [r2, r4]!"), 2, 0x100);
}

void InstructionTests::strWithRegisterOffset()
{
    cpu->setGeneralRegister(8, 0xfad15ded);
    cpu->setGeneralRegister(5, 0x4);
    cpu->setGeneralRegister(7, 0x8);

    // Without writeback
    assert_Instruction(0xe7858007, QString("str r8, [r5, r7]"), 5, 0x4);
    Q_ASSERT(cpu->getRAM()->ReadWord(0xc) == 0xfad15ded);

    // With writeback
    cpu->setGeneralRegister(0, 0x00d1ebaf);
    assert_Instruction(0xe7a50007, QString("str r0, [r5, r7]!"), 5, 0xc);
    Q_ASSERT(cpu->getRAM()->ReadWord(0xc) == 0x00d1ebaf);
}

void InstructionTests::pushpopWithoutWriteback()
{
    cpu->setGeneralRegister(13, 0x7000);
    cpu->setGeneralRegister(2, 2);
    cpu->setGeneralRegister(4, 4);
    cpu->setGeneralRegister(6, 6);
    assert_Instruction(0xe90d0054, QString("stmdb r13, { r2, r4, r6 }"), 13, 0x7000);
    Q_ASSERT(cpu->getRAM()->ReadWord(0x7000-(4*1)) == 6);
    Q_ASSERT(cpu->getRAM()->ReadWord(0x7000-(4*2)) == 4);
    Q_ASSERT(cpu->getRAM()->ReadWord(0x7000-(4*3)) == 2);

    cpu->setGeneralRegister(13, 0x6ff4);
    assert_Instruction(0xe8dd002a, QString("ldmia r13, { r1, r3, r5 }"), 13, 0x6ff4);
    Q_ASSERT(cpu->getGeneralRegister(1) == 2);
    Q_ASSERT(cpu->getGeneralRegister(3) == 4);
    Q_ASSERT(cpu->getGeneralRegister(5) == 6);
}

void InstructionTests::pushpopWithWriteback()
{
    cpu->setGeneralRegister(13, 0x7000);
    cpu->setGeneralRegister(1, 1);
    cpu->setGeneralRegister(3, 3);
    cpu->setGeneralRegister(5, 5);
    assert_Instruction(0xe92d002a, QString("stmdb r13!, { r1, r3, r5 }"), 13, 0x6ff4);
    Q_ASSERT(cpu->getRAM()->ReadWord(0x7000-(4*1)) == 5);
    Q_ASSERT(cpu->getRAM()->ReadWord(0x7000-(4*2)) == 3);
    Q_ASSERT(cpu->getRAM()->ReadWord(0x7000-(4*3)) == 1);

    assert_Instruction(0xe8fd0054, QString("ldmia r13!, { r2, r4, r6 }"), 13, 0x7000);
    Q_ASSERT(cpu->getGeneralRegister(2) == 1);
    Q_ASSERT(cpu->getGeneralRegister(4) == 3);
    Q_ASSERT(cpu->getGeneralRegister(6) == 5);
}

QTEST_APPLESS_MAIN(InstructionTests)

#include "tst_instructiontests.moc"
