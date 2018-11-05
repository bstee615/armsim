#ifndef STATUSREGISTERINSTRUCTION_H
#define STATUSREGISTERINSTRUCTION_H

#include "instruction.h"
#include "instructionoperand.h"

class StatusRegisterInstruction : public Instruction
{
    bool MRS;
    bool R;
    byte fieldMask;
    byte rDIndex;

    InstructionOperand *addressingMode;

public:
    StatusRegisterInstruction(word w, RegisterMemory *_registers);

    QString toString() override;
    void execute() override;
};

#endif // STATUSREGISTERINSTRUCTION_H
