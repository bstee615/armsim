#include <QtTest>

#include "loader.h"
#include "elf.h"

class LoaderTests : public QObject
{
    Q_OBJECT

    RAM ram;
    Elf32_Ehdr elfHeader;
    Elf32_Phdr *programHeaders;

public:
    LoaderTests() { }
    ~LoaderTests() { }

private slots:
    void initTestCase();

    void IsThereEnoughMemory_Success();
    void IsThereEnoughMemory_FailsNotEnoughMemory();

    void containsELFSignature_Success();
};

void LoaderTests::initTestCase()
{
    ram = RAM(100);

    elfHeader.e_phnum = 1;
    memcpy(elfHeader.e_ident, "\x7f""ELF", 4);

    programHeaders = new Elf32_Phdr[1];
    Elf32_Phdr programHeader;
    programHeader.p_offset = 0;
    programHeader.p_filesz = 100;
    programHeaders[0] = programHeader;
}

void LoaderTests::IsThereEnoughMemory_Success()
{
    Q_ASSERT(isThereEnoughMemory(ram, elfHeader, programHeaders));
}

void LoaderTests::IsThereEnoughMemory_FailsNotEnoughMemory()
{
    ram = RAM(99);
    Q_ASSERT(isThereEnoughMemory(ram, elfHeader, programHeaders) == false);
}

void LoaderTests::containsELFSignature_Success()
{
    Q_ASSERT(containsELFSignature(elfHeader.e_ident));
}

QTEST_APPLESS_MAIN(LoaderTests)

#include "tst_loadertests.moc"
