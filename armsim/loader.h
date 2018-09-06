#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include "ram.h"
#include "elf.h"

bool containsELFSignature (unsigned char* e_ident);
bool isThereEnoughMemory(RAM &ram, Elf32_Ehdr &elfHeader, Elf32_Phdr* programHeaders);
bool loadELF(QString filename, RAM& ram);

#endif // LOADER_H
