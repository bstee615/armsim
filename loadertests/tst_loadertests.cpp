/* tst_loadertests.cpp
 * Unit tests for the Loader methods.
 */

#include <QtTest>

#include "loader.h"
#include "elf.h"
#include "cpu.h"

class LoaderTests : public QObject
{
    Q_OBJECT

    Memory ram;
    Elf32_Ehdr elfHeader;
    Elf32_Phdr *programHeaders;

public:
    LoaderTests() { }
    ~LoaderTests() { }

private slots:
    void initTestCase();
    void init();

    void IsThereEnoughMemory_Success();
    void IsThereEnoughMemory_FailsNotEnoughMemory();

    void containsELFSignature_Success();

    void loadELF_SuccessTest1();
    void loadELF_SuccessTest2();
    void loadELF_SuccessTest3();
};

void LoaderTests::initTestCase()
{
    ram = Memory(100);

    elfHeader.e_phnum = 1;
    memcpy(elfHeader.e_ident, "\x7f""ELF", 4);

    programHeaders = new Elf32_Phdr[1];
    Elf32_Phdr programHeader;
    programHeader.p_offset = 0;
    programHeader.p_filesz = 100;
    programHeaders[0] = programHeader;
}

void LoaderTests::init()
{
    ram.clearMemory();
}

void LoaderTests::IsThereEnoughMemory_Success()
{
    Q_ASSERT(isThereEnoughMemory(ram, elfHeader, programHeaders));
}

void LoaderTests::IsThereEnoughMemory_FailsNotEnoughMemory()
{
    ram = Memory(99);
    Q_ASSERT(isThereEnoughMemory(ram, elfHeader, programHeaders) == false);
}

void LoaderTests::containsELFSignature_Success()
{
    Q_ASSERT(containsELFSignature(elfHeader.e_ident));
}

void LoaderTests::loadELF_SuccessTest1()
{
    Memory ram = Memory(32768);
    loadELF("testfiles\\loader\\test1.exe", new CPU(&ram));
    Q_ASSERT(ram.Checksum() == 536861081);
}

void LoaderTests::loadELF_SuccessTest2()
{
    Memory ram = Memory(32768);
    loadELF("testfiles\\loader\\test2.exe", new CPU(&ram));
    Q_ASSERT(ram.Checksum() == 536864433);
}

void LoaderTests::loadELF_SuccessTest3()
{
    Memory ram = Memory(32768);
    loadELF("testfiles\\loader\\test3.exe", new CPU(&ram));
    Q_ASSERT(ram.Checksum() == 536861199);
}

QTEST_APPLESS_MAIN(LoaderTests)

#include "tst_loadertests.moc"
