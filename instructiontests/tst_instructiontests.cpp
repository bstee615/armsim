#include <QtTest>

#include "memory.h"
#include "dataprocessinginstruction.h"

class InstructionTests : public QObject
{
    Q_OBJECT

    Memory *ram;
    Memory *registers;

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
};

InstructionTests::InstructionTests(): ram(new Memory(100)), registers(new Memory(72))
{
}

InstructionTests::~InstructionTests()
{
    delete ram;
    delete registers;
}

void InstructionTests::init()
{
    registers->clearMemory();
    ram->clearMemory();

    registers->WriteWord(13 * 4, 0x7000);
}

void InstructionTests::cleanup()
{
    ram->clearMemory();
    registers->clearMemory();
}

void InstructionTests::mov_Success()
{
    DataProcessingInstruction *instr = new DataProcessingInstruction(0xe3a02030, registers);
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), QString("mov r2, #48")) == 0);

    Q_ASSERT(registers->ReadWord(2*4) == 0);
    instr->execute();
    Q_ASSERT(registers->ReadWord(2*4) == 48);
}

void InstructionTests::movAndRotate_Success()
{
    DataProcessingInstruction *instr = new DataProcessingInstruction(0xe3a00fb5, registers);
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), QString("mov r0, #724")) == 0);

    Q_ASSERT(registers->ReadWord(0) == 0);
    instr->execute();
    Q_ASSERT(registers->ReadWord(0) == 724);
}

void InstructionTests::movWithImmediateShiftedRegister_Success()
{
    DataProcessingInstruction *instr = new DataProcessingInstruction(0xe1a02141, registers);
    Q_ASSERT(instr != nullptr);

    registers->WriteWord(1*4, 0xa1000000);
    Q_ASSERT(QString::compare(instr->toString(), QString("mov r2, r1, asr #2")) == 0);

    Q_ASSERT(registers->ReadWord(2*4) == 0);
    instr->execute();
    Q_ASSERT(registers->ReadWord(2*4) == 0xe8400000);
}

void InstructionTests::add_Success()
{
    DataProcessingInstruction *instr = new DataProcessingInstruction(0xe285200F, registers);
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), QString("add r2, r5, #15")) == 0);

    Q_ASSERT(registers->ReadWord(2*4) == 0);
    instr->execute();
    Q_ASSERT(registers->ReadWord(2*4) == 15);
}

QTEST_APPLESS_MAIN(InstructionTests)

#include "tst_instructiontests.moc"
