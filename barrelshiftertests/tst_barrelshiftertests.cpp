#include <QtTest>
#include <QDebug>

#include "barrelshifter.h"
#include "memory.h"

class BarrelShifterTests : public QObject
{
    Q_OBJECT

public:
    BarrelShifterTests();
    ~BarrelShifterTests();

private slots:
    void ror_ZeroRotations();
    void ror_Wrap();
    void ror_NoWrap();

    void lsl_ZeroShifts();
    void lsl_Success();
    void lsl_Overflow();

    void lsr_ZeroShifts();
    void lsr_Success();
    void lsr_Overflow();
    void lsr_SignExtend();

    void asr_ZeroShifts();
    void asr_Success();
    void asr_Overflow();
    void asr_SignExtend();
};

BarrelShifterTests::BarrelShifterTests()
{

}

BarrelShifterTests::~BarrelShifterTests()
{

}

void BarrelShifterTests::ror_ZeroRotations()
{
    const word target = 0x0000FF00;
    word w = target;
    w = BarrelShifter::ror(w, 0);
    Q_ASSERT(w == target);
}

void BarrelShifterTests::ror_Wrap()
{
    word w = 0x000000FF;
    w = BarrelShifter::ror(w, 4);
    Q_ASSERT(w == 0xF000000F);
}

void BarrelShifterTests::ror_NoWrap()
{
    word w = 0x0000FF00;
    w = BarrelShifter::ror(w, 4);
    qDebug () << w << 0x00000FF0;
    Q_ASSERT(w == 0x00000FF0);
}

void BarrelShifterTests::lsl_ZeroShifts()
{
    const word target = 0x0000FF00;
    word w = target;
    w = BarrelShifter::lsl(w, 0);
    Q_ASSERT(w == target);
}

void BarrelShifterTests::lsl_Success()
{
    word w = 0x0000FF00;
    w = BarrelShifter::lsl(w, 4);
    Q_ASSERT(w == 0x000FF000);
}

void BarrelShifterTests::lsl_Overflow()
{
    word w = 0xFF000000;
    w = BarrelShifter::lsl(w, 4);
    Q_ASSERT(w == 0xF0000000);
}

void BarrelShifterTests::lsr_ZeroShifts()
{
    const word target = 0x00FF0000;
    word w = target;
    w = BarrelShifter::lsr(w, 0);
    Q_ASSERT(w == target);
}

void BarrelShifterTests::lsr_Success()
{
    int32_t w = 0xa1000000;
    w = BarrelShifter::lsr(w, 2);
    Q_ASSERT(w == 0x28400000);
}

void BarrelShifterTests::lsr_Overflow()
{
    const word target = 0x000000FF;
    word w = target;
    w = BarrelShifter::lsr(w, 4);
    Q_ASSERT(w == 0x0000000F);
}

void BarrelShifterTests::lsr_SignExtend()
{
    int32_t w = 0xFFFFFFFF;
    w = BarrelShifter::lsr(w, 4);
    Q_ASSERT(w == 0x0FFFFFFF);
}

void BarrelShifterTests::asr_ZeroShifts()
{
    int32_t w = 0x0000FF00;
    w = BarrelShifter::asr(w, 0);
    Q_ASSERT(w == 0x0000FF00);
}

void BarrelShifterTests::asr_Success()
{
    int32_t w = 0xa1000000;
    w = BarrelShifter::asr(w, 2);
    Q_ASSERT(w == 0xe8400000);
}

void BarrelShifterTests::asr_Overflow()
{
    int32_t w = 0x000000FF;
    w = BarrelShifter::asr(w, 4);
    Q_ASSERT(w == 0x0000000F);
}

void BarrelShifterTests::asr_SignExtend()
{
    word w = 0x80000000;
    w = BarrelShifter::asr(w, 4);
    Q_ASSERT(w == 0xF8000000);
}

QTEST_APPLESS_MAIN(BarrelShifterTests)

#include "tst_barrelshiftertests.moc"
