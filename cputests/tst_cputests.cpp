#include <QtTest>
#include <QDebug>

#include "cpu.h"
#include "memory.h"
#include "currenttime.h"

class CPUTests : public QObject
{
    Q_OBJECT
    CPU *cpu;
    Memory *ram;

public:
    ~CPUTests();

private slots:
    void initTestCase();
    void init();

    void fetch_Success();
    void decode_Success();
    void execute_Success();

    void PC_Success();
    void NZCF_Success();
    void GeneralRegisters_Success();
};

CPUTests::~CPUTests()
{
    delete ram;
    delete cpu;
}

void CPUTests::initTestCase()
{
    ram = new Memory(100);
    cpu = new CPU(ram);
}

void CPUTests::init()
{
    ram->clearMemory();
    cpu->getRegisters()->clearMemory();
}

void CPUTests::fetch_Success()
{
    const address addr = 20;
    const word targetValue = 0xABADABAA;

    ram->WriteWord(addr, targetValue);
    cpu->setProgramCounter(addr);
    Q_ASSERT(cpu->fetch() == targetValue);
}

void CPUTests::decode_Success()
{
    Instruction *instr = cpu->decode(0xe3a02030);
    Q_ASSERT(instr != nullptr);

    Q_ASSERT(QString::compare(instr->toString(), QString("mov r2, #48")) == 0);

    Q_ASSERT(cpu->getGeneralRegister(2) == 0);
    cpu->execute(instr);
    Q_ASSERT(cpu->getGeneralRegister(2) == 48);
}

void CPUTests::execute_Success()
{
    // TODO: Update this test when functionality is added to execute().
    // This line may not be necessary, but it's future-proofing for now.
    cpu->decode(cpu->fetch());

    auto begin = get_ms_since_epoch();
    cpu->execute(nullptr);
    auto end = get_ms_since_epoch();
    Q_ASSERT(end - begin >= 250);
}

void CPUTests::PC_Success()
{
    Q_ASSERT(cpu->getProgramCounter() == 0);
    const address addr = 56;
    cpu->setProgramCounter(addr);
    Q_ASSERT(cpu->getProgramCounter() == addr);
}

void CPUTests::NZCF_Success()
{
    Q_ASSERT(cpu->getNZCF() == 0);
    cpu->setNZCFFlag(NZCFFlag::Negative, true);
    Q_ASSERT(cpu->getNZCF() == 0b1000);
    cpu->setNZCFFlag(NZCFFlag::Carry, true);
    Q_ASSERT(cpu->getNZCF() == 0b1010);
    cpu->setNZCFFlag(NZCFFlag::Zero, true);
    Q_ASSERT(cpu->getNZCF() == 0b1110);
    cpu->setNZCFFlag(NZCFFlag::Overflow, false);
    Q_ASSERT(cpu->getNZCF() == 0b1110);
    cpu->setNZCFFlag(NZCFFlag::Overflow, true);
    Q_ASSERT(cpu->getNZCF() == 0b1111);
    cpu->setNZCFFlag(NZCFFlag::Zero, false);
    Q_ASSERT(cpu->getNZCF() == 0b1011);
}

void CPUTests::GeneralRegisters_Success()
{
    const unsigned int selectedRegister = 1;
    const word targetValue = 0xFABADABA;

    for (unsigned int i = 0; i <= 14; i ++) {
        Q_ASSERT(cpu->getGeneralRegister(i) == 0);
    }

    Q_ASSERT(cpu->getGeneralRegister(selectedRegister) == 0);
    cpu->setGeneralRegister(selectedRegister, targetValue);
    Q_ASSERT(cpu->getGeneralRegister(selectedRegister) == targetValue);

    for (unsigned int i = 0; i <= 14; i ++) {
        if (i != selectedRegister) Q_ASSERT(cpu->getGeneralRegister(i) == 0);
    }
}


QTEST_APPLESS_MAIN(CPUTests)

#include "tst_cputests.moc"
