#include <QtTest>

// add necessary includes here

class LoaderTests : public QObject
{
    Q_OBJECT

public:
    LoaderTests();
    ~LoaderTests();

private slots:
    void test_case1();

};

LoaderTests::LoaderTests()
{

}

LoaderTests::~LoaderTests()
{

}

void LoaderTests::test_case1()
{

}

QTEST_APPLESS_MAIN(LoaderTests)

#include "tst_loadertests.moc"
