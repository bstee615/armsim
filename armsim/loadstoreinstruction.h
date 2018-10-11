/* loadstoreinstruction.h
 * Models a ldr or str instruction.
*/

#ifndef LOADSTOREINSTRUCTION_H
#define LOADSTOREINSTRUCTION_H

#include <QString>
#include "memory.h"
#include "instruction.h"
#include "instructionoperand.h"

class LoadStoreInstruction: public Instruction
{
    bool P; // false: Pre-Indexed / true: Post-Indexed
    bool U; // false: Offset is positive / true: Offset is negative
    bool B; // false: Word / true: Unsigned Byte
    bool W; // false: No Writeback / true: Writeback
    bool L; // false: Store / true: Load

    Memory *ram; // A reference to the RAM memory instance from the CPU.
    Memory *registers; // A reference to the register memory instance from the CPU.
    address rDIndex; // Index of the destination register from 0-15
    address rNIndex; // Index of register n from 0-15

    InstructionOperand *addressingMode; // Addressing mode operand

public:
    LoadStoreInstruction(word w, Memory *ram, Memory *registers);

    QString toString();
    void execute();
};

#endif // LOADSTOREINSTRUCTION_H
