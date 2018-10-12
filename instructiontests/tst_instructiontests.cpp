#include <QtTest>

#include "cpu.h"
#include "memory.h"
#include "dataprocessinginstruction.h"
#include "mulinstruction.h"

class InstructionTests : public QObject
{
    Q_OBJECT

    CPU *cpu;

public:
    InstructionTests();
    ~InstructionTests();

private slots:
    void init();
    void cleanup();
    void mov_Success();
    void movAndRotate_Success();
    void movWithImmediateShiftedRegister_Success();
    void add_Success();
    void mul_Success();
};

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

void InstructionTests::mov_Success()
{
    Instruction *instr = cpu->decode(0xe3a02030);;
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), QString("mov r2, #48")) == 0);

    Q_ASSERT(cpu->getGeneralRegister(2) == 0);
    instr->execute();
    Q_ASSERT(cpu->getGeneralRegister(2) == 48);
}

void InstructionTests::movAndRotate_Success()
{
    Instruction *instr = cpu->decode(0xe3a00fb5);
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), QString("mov r0, #724")) == 0);

    Q_ASSERT(cpu->getGeneralRegister(0) == 0);
    instr->execute();
    Q_ASSERT(cpu->getGeneralRegister(0) == 724);
}

void InstructionTests::movWithImmediateShiftedRegister_Success()
{
    cpu->setGeneralRegister(1, 0xa1000000);
    Instruction *instr = cpu->decode(0xe1a02141);
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), QString("mov r2, r1, asr #2")) == 0);

    Q_ASSERT(cpu->getGeneralRegister(2) == 0);
    instr->execute();
    Q_ASSERT(cpu->getGeneralRegister(2) == 0xe8400000);
}

void InstructionTests::add_Success()
{
    Instruction *instr = cpu->decode(0xe285200F);
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), QString("add r2, r5, #15")) == 0);

    Q_ASSERT(cpu->getGeneralRegister(2) == 0);
    instr->execute();
    Q_ASSERT(cpu->getGeneralRegister(2) == 15);
}

void InstructionTests::mul_Success()
{
    cpu->setGeneralRegister(1, 0xa1000000);
    cpu->setGeneralRegister(2, 0x00001050);
    Instruction *instr = cpu->decode(0xe0050291);
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), QString("mul r5, r1, r2")) == 0);

    Q_ASSERT(cpu->getGeneralRegister(5) == 0);
    instr->execute();
    Q_ASSERT(cpu->getGeneralRegister(5) == 0x50000000);
}

QTEST_APPLESS_MAIN(InstructionTests)

#include "tst_instructiontests.moc"
