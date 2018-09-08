/* loader.h
 * Contains definitions for utility methods to use to load programs from a file into RAM.
 */

#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include "ram.h"
#include "elf.h"

// Returns true if the specified char array holds the magic ELF heade: "<DEL>ELF".
bool containsELFSignature (unsigned char* e_ident);
// Returns true if ram is large enough to hold the data specified by programHeaders.
bool isThereEnoughMemory(RAM &ram, Elf32_Ehdr &elfHeader, Elf32_Phdr* programHeaders);
// loads an ELF file into the specified RAM object.
bool loadELF(QString filename, RAM& ram);

#endif // LOADER_H
