/* loadstoreinstruction.h
 * Models a ldr or str instruction.
*/

#ifndef LOADSTOREINSTRUCTION_H
#define LOADSTOREINSTRUCTION_H

#include <QString>
#include "instruction.h"
#include "instructionoperand.h"
#include "registermemory.h"

class LoadStoreInstruction: public Instruction
{
    bool P; // false: Pre-Indexed / true: Post-Indexed
    bool U; // false: Offset is positive / true: Offset is negative
    bool B; // false: Word / true: Unsigned Byte
    bool W; // false: No Writeback / true: Writeback
    bool L; // false: Store / true: Load

    Memory *ram; // A reference to the RAM memory instance from the CPU.
    byte rDIndex; // Index of the destination register from 0-15
    word rDValue;
    byte rNIndex; // Index of register n from 0-15
    word rNValue;

    InstructionOperand *addressingMode; // Addressing mode operand

    QString addressingModeToString();

public:
    LoadStoreInstruction(word w, Memory *ram, RegisterMemory *registers);

    QString toString() override;
    void execute() override;
};

#endif // LOADSTOREINSTRUCTION_H
