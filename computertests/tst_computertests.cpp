#include <QtTest>
#include <QDebug>

#include "computer.h"
#include "testfiles.h"

#define TRACE_NAME "trace.log"

class ComputerTests : public QObject
{
    Q_OBJECT

    Computer *computer;

public:
    ComputerTests();

private slots:
    void cleanup();

    void run_Success();
    void step_Success();
};

ComputerTests::ComputerTests()
{
    computer = new Computer(32768);
}

void ComputerTests::cleanup()
{
    computer->cpu.getRAM()->clearMemory();
}

void ComputerTests::run_Success()
{
    bool b = false;
    computer->cpu.getRAM()->WriteWord(0x40, 0xef000011); // Write SWI at 0x40
    computer->run(&b);
    Q_ASSERT(computer->cpu.getProgramCounter() == 0x44);
}

void ComputerTests::step_Success()
{
    Q_ASSERT(computer->step() == 1); // Successfully got 0.
}

QTEST_APPLESS_MAIN(ComputerTests)

#include "tst_computertests.moc"
