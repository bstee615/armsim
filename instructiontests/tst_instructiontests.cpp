#include <QtTest>

#include "memory.h"
#include "dataprocessinginstruction.h"

class InstructionTests : public QObject
{
    Q_OBJECT

    Memory *memory;
    Memory *registers;

public:
    InstructionTests();
    ~InstructionTests();

private slots:
    void init();
    void cleanup();
    void mov_Success();
    void add_Success();
};

InstructionTests::InstructionTests(): memory(new Memory(100)), registers(new Memory(72))
{
    registers->WriteWord(13 * 4, 0x7000);
}

InstructionTests::~InstructionTests()
{
    delete memory;
    delete registers;
}

void InstructionTests::init()
{

}

void InstructionTests::cleanup()
{
    memory->clearMemory();
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
