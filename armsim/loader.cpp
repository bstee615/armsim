#include "loader.h"
#include "elf.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

int min(int a, int b)
{
    return (a < b) ? b : a;
}

bool containsELFSignature (unsigned char* e_ident)
{
    return (e_ident[0] == '\x7f' &&
            e_ident[1] == 'E' &&
            e_ident[2] == 'L' &&
            e_ident[3] == 'F');
}

QString toBits(word number)
{
    return QString("%1").arg(number, 32, 2, QChar('0'));
}

void writeBytesToRAM(ifstream &strm, RAM &ram, Elf32_Ehdr &elfHeader, Elf32_Phdr* programHeaders)
{
    for (size_t ph_i = 0; ph_i < elfHeader.e_phnum; ph_i ++) {
        Elf32_Phdr &progHeader = programHeaders[ph_i];
        byte *data = new byte[progHeader.p_filesz];
        strm.seekg(progHeader.p_offset);
        strm.read((char *)data, progHeader.p_filesz * 1);

        for (address i = 0; i < progHeader.p_filesz; i ++) {
//            qDebug() << "Loader:" << "Writing" << toBits(data[i]) << "from byte" << progHeader.p_offset + i << "to address" << (progHeader.p_paddr + i);
            ram.WriteByte(progHeader.p_paddr + i, data[i]);
        }
        delete[] data;
    }
}

void fetchELFHeader(ifstream &strm, Elf32_Ehdr &elfHeader)
{
    if (!strm) {
        qDebug() << "Loader:" << "Unable to open input file.";
        return;
    }

    // read ELF header
    strm.read((char *)&elfHeader, sizeof(elfHeader));

    if (!strm) {
        qDebug() << "Loader:"  << "Error reading ELF header.";
        return;
    }

    if (!containsELFSignature(elfHeader.e_ident)) {
        qDebug() << "Loader:"  << "Input file is not an ELF file.";
        return;
    }

    qDebug() << "Loader:" << "Entry point:" << elfHeader.e_entry;
    qDebug() << "Loader:" << "Found" << elfHeader.e_phnum << "segments";
}

Elf32_Phdr* fetchProgramHeaders(ifstream &strm, Elf32_Ehdr elfHeader)
{
    Elf32_Phdr *headers = new Elf32_Phdr[elfHeader.e_phnum];

    strm.seekg(elfHeader.e_phoff);
    for (size_t i = 0; i < elfHeader.e_phnum; i ++) {
        Elf32_Phdr progHeader;
        char *data = new char[elfHeader.e_phentsize];

        strm.read(data, elfHeader.e_phentsize);
        memcpy(&progHeader, data, min(sizeof(progHeader), (unsigned int) elfHeader.e_phentsize));
        delete[] data;

        headers[i] = progHeader;

        qDebug() << "Loader:" << "Segment" << i << "offset: " << progHeader.p_offset;
        qDebug() << "Loader:" << "Segment" << i << "length: " << progHeader.p_filesz;
        qDebug() << "Loader:" << "Segment" << i << "load address: " << progHeader.p_paddr;
    }

    return headers;
}

void loadELF(QString filename, RAM &ram)
{
    ram.clearMemory();

    ifstream strm;
    Elf32_Ehdr elfHeader;

    // Converted to std C string for better formatting
    qDebug() << "Loader:" << "Opening file" << filename.toStdString().c_str();
    strm.open(filename.toStdString().c_str());

    fetchELFHeader(strm, elfHeader);

    Elf32_Phdr* programHeaders = fetchProgramHeaders(strm, elfHeader);
    writeBytesToRAM(strm, ram, elfHeader, programHeaders);

    delete[] programHeaders;
    strm.close();

    qDebug() << "Loader:" << "RAM checksum after loading:" << ram.Checksum();

    return;
}
