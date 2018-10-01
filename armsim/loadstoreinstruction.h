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
    bool p; // false: Pre-Indexed / true: Post-Indexed
    bool u; // false: Offset is positive / true: Offset is negative
    bool b; // false: Word / true: Unsigned Byte
    bool w; // false: No Writeback / true: Writeback
    bool l; // false: Store / true: Load

    Memory *ram; // A reference to the RAM memory instance from the CPU.
    Memory *registers; // A reference to the register memory instance from the CPU.
    byte *rDIndex; // Index of the destination register from 0-15
    byte *rNIndex; // Index of register n from 0-15

    InstructionOperand *addressingMode; // Addressing mode operand

public:
    LoadStoreInstruction(word w, Memory *ram, Memory *registers);

    QString toString();
    void execute();
};

#endif // LOADSTOREINSTRUCTION_H
