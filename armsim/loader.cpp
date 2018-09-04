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

Elf32_Phdr* readProgramHeaders(ifstream &strm, Elf32_Ehdr elfHeader)
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

void writeBytesToRAM(ifstream &strm, RAM &ram, Elf32_Ehdr &elfHeader, Elf32_Phdr* programHeaders)
{
    for (size_t ph_i = 0; ph_i < elfHeader.e_phnum; ph_i ++) {
        Elf32_Phdr &progHeader = programHeaders[ph_i];
        char *data = new char[progHeader.p_filesz];
        strm.read(data, progHeader.p_filesz);

        for (address i = 0; i < progHeader.p_filesz; i ++) {
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
}

void loadELFFile(QString filename, RAM &ram)
{
    ifstream strm;
    Elf32_Ehdr elfHeader;

    qDebug() << "Loader:" << "Opening file" << filename.split("/").last();
    strm.open(filename.toStdString().c_str());

    fetchELFHeader(strm, elfHeader);

    qDebug() << "Loader:" << "Entry point:" << elfHeader.e_entry;
    qDebug() << "Loader:" << "Found" << elfHeader.e_phnum << "segments";

    Elf32_Phdr* programHeaders = readProgramHeaders(strm, elfHeader);
    writeBytesToRAM(strm, ram, elfHeader, programHeaders);

    delete[] programHeaders;
    strm.close();

    qDebug() << ram.Checksum();

    return;
}
