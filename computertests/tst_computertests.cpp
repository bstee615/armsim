#include <QtTest>
#include <QDebug>

#include "computer.h"

class ComputerTests : public QObject
{
    Q_OBJECT

    Computer *computer;

public:
    ComputerTests();

private slots:
    void init();

    void run_Success();
    void step_Success();
};

const address bytes = 100;
const address targetAddress = 12;
const word targetValue = 0xDADFABEA;
const word fillValue = 0xFFFFFFFF;
ComputerTests::ComputerTests()
{
    computer = new Computer(bytes);
    for (unsigned int i = 0; i < targetAddress; i ++) {
        computer->cpu.getRAM()->WriteWord(targetAddress, fillValue);
    }
    computer->cpu.getRAM()->WriteWord(targetAddress, targetValue);
}

void ComputerTests::init()
{
}

void ComputerTests::run_Success()
{
    bool b = false;
    computer->run(&b);
    Q_ASSERT(computer->cpu.getProgramCounter() == 4);
}

void ComputerTests::step_Success()
{
    Q_ASSERT(computer->step() == 0);
}

QTEST_APPLESS_MAIN(ComputerTests)

#include "tst_computertests.moc"
