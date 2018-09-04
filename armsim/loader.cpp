#include "loader.h"
#include "elf.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

unsigned int min(unsigned int a, unsigned int b)
{
    return (a < b) ? a : b;
}

bool containsELFSignature (unsigned char* e_ident)
{
    return (e_ident[0] == '\x7f' &&
            e_ident[1] == 'E' &&
            e_ident[2] == 'L' &&
            e_ident[3] == 'F');
}

void loadELFFile(QString filename, RAM &ram)
{
    ifstream strm;
    Elf32_Ehdr elfHeader;

    strm.open(filename.toStdString().c_str());

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

    strm.seekg(elfHeader.e_phoff);

    for (int i = 0; i < elfHeader.e_phnum; i ++) {
        Elf32_Phdr progHeader;
        char *data = new char[elfHeader.e_phentsize];

        strm.read(data, elfHeader.e_phentsize);
        memcpy(&progHeader, data, min(sizeof(progHeader), (unsigned int) elfHeader.e_phentsize));
        delete[] data;

        qDebug() << "Loader:" << "Segment" << i << "offset: " << progHeader.p_offset;
        qDebug() << "Loader:" << "Segment" << i << "length: " << progHeader.p_filesz;
        qDebug() << "Loader:" << "Segment" << i << "load address: " << progHeader.p_paddr;

        // TODO: Load bytes from the location specified by progHeader to RAM.
    }

    strm.close();

    return;
}
