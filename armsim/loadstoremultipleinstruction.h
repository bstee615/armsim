#ifndef LOADSTOREMULTIPLEINSTRUCTION_H
#define LOADSTOREMULTIPLEINSTRUCTION_H

#include <QString>
#include "instruction.h"
#include "instructionoperand.h"
#include "memory.h"

class LoadStoreMultipleInstruction : public Instruction
{
    bool p; // false: Pre-Indexed / true: Post-Indexed
    bool u; // false: Offset is positive / true: Offset is negative
    bool s; // false: Do not set condition codes / true: Set condition codes
    bool w; // false: No Writeback / true: Writeback
    bool l; // false: Store / true: Load

    Memory *ram; // A reference to the RAM memory instance from the CPU.
    Memory *registers; // A reference to the register memory instance from the CPU.
    byte *rNIndex; // Index of register n from 0-15

    InstructionOperand *addressingMode;
    halfword registerList;

public:
    LoadStoreMultipleInstruction(word w, Memory *ram, Memory *registers);

    QString toString() override;
    void execute() override;
};

#endif // LOADSTOREMULTIPLEINSTRUCTION_H
