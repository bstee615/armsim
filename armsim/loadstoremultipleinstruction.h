#ifndef LOADSTOREMULTIPLEINSTRUCTION_H
#define LOADSTOREMULTIPLEINSTRUCTION_H

#include <QString>
#include "instruction.h"
#include "instructionoperand.h"
#include "memory.h"

class LoadStoreMultipleInstruction : public Instruction
{
    bool P; // false: Pre-Indexed / true: Post-Indexed
    bool U; // false: Offset is positive / true: Offset is negative
    bool S; // false: Do not set condition codes / true: Set condition codes
    bool W; // false: No Writeback / true: Writeback
    bool L; // false: Store / true: Load

    Memory *registers;
    Memory *ram; // A reference to the RAM memory instance from the CPU.
    word rNIndex; // Index of register n from 0-15
    word rNValue;

    InstructionOperand *addressingMode;
    halfword registerList;

public:
    LoadStoreMultipleInstruction(word w, Memory *_ram, Memory *registers);

    QString toString() override;
    void execute() override;
};

#endif // LOADSTOREMULTIPLEINSTRUCTION_H
