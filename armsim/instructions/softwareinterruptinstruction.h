/* softwareinterruptinstruction.h
 * Models a Software Interrupt instruction that halts CPU execution.
*/

#ifndef SOFTWAREINTERRUPTINSTRUCTION_H
#define SOFTWAREINTERRUPTINSTRUCTION_H

#include "instruction.h"
#include "registermemory.h"

class SoftwareInterruptInstruction : public Instruction
{
    word pcValue;

public:
    word interruptCode; // 24-bit interrupt code, to be ignored by the processor and used by the OS.
    SoftwareInterruptInstruction(word w, RegisterMemory *_registers);

    QString toString() override;
    void execute() override;
};

#endif // SOFTWAREINTERRUPTINSTRUCTION_H
