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

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
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
    return QString("%1").arg(number, 8, 2, QChar('0'));
}

bool isThereEnoughMemory(RAM &ram, Elf32_Ehdr &elfHeader, Elf32_Phdr* programHeaders)
{
    size_t sizeOfAllSegments = 0;
    for (int ph_i = 0; ph_i < elfHeader.e_phnum; ph_i ++) {
        sizeOfAllSegments += programHeaders[ph_i].p_filesz;
    }

    size_t spaceItsGonnaTake = programHeaders[0].p_offset + sizeOfAllSegments;
    if (ram.getSize() < spaceItsGonnaTake) {
        qCritical() << "Loader:" << "Error writing bytes to RAM; not enough memory.";
        return false;
    }

    return true;
}

bool writeBytesToRAM(fstream &strm, RAM &ram, Elf32_Ehdr &elfHeader, Elf32_Phdr* programHeaders)
{
    if (!isThereEnoughMemory(ram, elfHeader, programHeaders)) {
        return false;
    }

    for (size_t ph_i = 0; ph_i < elfHeader.e_phnum; ph_i ++) {
        Elf32_Phdr &progHeader = programHeaders[ph_i];
        strm.seekg(progHeader.p_offset);
        byte *data = new byte[progHeader.p_filesz];
        for (address i = 0; i < progHeader.p_filesz; i ++) {
            data[i] = 0;
        }
        strm.read((char*)data, progHeader.p_filesz * sizeof(byte));
        if (!strm) {
            qCritical() << "Loader:"  << "Error reading program bytes from segment" << QString::number(ph_i) + ":" << strerror(errno);
            return false;
        }

        for (address i = 0; i < progHeader.p_filesz; i ++) {
            ram.WriteByte(progHeader.p_paddr + i, data[i]);
        }
        delete[] data;
    }

    return true;
}

int fetchELFHeader(fstream &strm, Elf32_Ehdr &elfHeader)
{
    if (!strm) {
        qCritical() << "Loader:" << "Unable to open input file.";
        return false;
    }

    strm.read((char *)&elfHeader, sizeof(elfHeader));

    if (!strm) {
        qCritical() << "Loader:"  << "Error reading ELF header:" << strerror(errno);
        return false;
    }

    if (!containsELFSignature(elfHeader.e_ident)) {
        qCritical() << "Loader:"  << "Input file is not an ELF file.";
        return false;
    }

    qDebug() << "Loader:" << "Entry point:" << elfHeader.e_entry;
    qDebug() << "Loader:" << "Found" << elfHeader.e_phnum << "segments";
    return true;
}

Elf32_Phdr* fetchProgramHeaders(fstream &strm, Elf32_Ehdr elfHeader)
{
    Elf32_Phdr *headers = new Elf32_Phdr[elfHeader.e_phnum];

    strm.seekg(elfHeader.e_phoff);
    for (size_t i = 0; i < elfHeader.e_phnum; i ++) {
        Elf32_Phdr progHeader;
        char *data = new char[elfHeader.e_phentsize];

        strm.read(data, elfHeader.e_phentsize);
        if (!strm) {
            qCritical() << "Loader:"  << "Error reading program header table:" << strerror(errno);
            return nullptr;
        }

        memcpy(&progHeader, data, min(sizeof(progHeader), (unsigned int) elfHeader.e_phentsize));
        delete[] data;

        headers[i] = progHeader;

        qDebug() << "Loader:" << "Segment" << i << "offset: " << progHeader.p_offset;
        qDebug() << "Loader:" << "Segment" << i << "length: " << progHeader.p_filesz;
        qDebug() << "Loader:" << "Segment" << i << "load address: " << progHeader.p_paddr;
    }

    return headers;
}

bool loadELF(QString filename, RAM &ram)
{
    ram.clearMemory();

    if (filesize(filename.toStdString().c_str()) < sizeof(Elf32_Ehdr)) {
        qCritical() << "Loader:"  << "Input file is not an ELF file.";
        return false;
    }

    fstream strm(filename.toStdString().c_str(), ios::binary | ios::in);
    Elf32_Ehdr elfHeader;

    // Converted to std C string for better formatting
    qDebug() << "Loader:" << "Opening file" << filename.toStdString().c_str();

    if (!fetchELFHeader(strm, elfHeader)) {
        return false;
    }

    Elf32_Phdr* programHeaders = fetchProgramHeaders(strm, elfHeader);
    if (fetchProgramHeaders == nullptr) {
        return false;
    }
    if (!writeBytesToRAM(strm, ram, elfHeader, programHeaders)) {
        return false;
    }
    delete[] programHeaders;
    strm.close();

    qDebug() << "Loader:" << "RAM checksum after loading:" << ram.Checksum();

    return true;
}
