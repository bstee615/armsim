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
    void init();

    void run_Success();
    void step_Success();
};

const address bytes = 32768;
ComputerTests::ComputerTests()
{
    computer = new Computer(bytes);
}

void ComputerTests::init()
{
}

void ComputerTests::run_Success()
{
    bool b = false;
    computer->run(&b);
}

void ComputerTests::step_Success()
{
    Q_ASSERT(computer->step() == 0);
}

QTEST_APPLESS_MAIN(ComputerTests)

#include "tst_computertests.moc"
