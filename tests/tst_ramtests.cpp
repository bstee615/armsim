#include <QtTest>

// add necessary includes here

class RAMTests : public QObject
{
    Q_OBJECT

public:
    RAMTests();
    ~RAMTests();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

RAMTests::RAMTests()
{

}

RAMTests::~RAMTests()
{

}

void RAMTests::initTestCase()
{

}

void RAMTests::cleanupTestCase()
{

}

void RAMTests::test_case1()
{

}

QTEST_APPLESS_MAIN(RAMTests)

#include "tst_ramtests.moc"
