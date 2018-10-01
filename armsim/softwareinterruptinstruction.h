/* softwareinterruptinstruction.h
 * Models a Software Interrupt instruction that halts CPU execution.
*/

#ifndef SOFTWAREINTERRUPTINSTRUCTION_H
#define SOFTWAREINTERRUPTINSTRUCTION_H

#include "instruction.h"
#include "memorytypes.h"

class SoftwareInterruptInstruction : public Instruction
{
    word interruptNumber; // 24-bit interrupt code, to be ignored by the processor and used by the OS.

public:
    SoftwareInterruptInstruction(word w);

    QString toString();
    void execute();
};

#endif // SOFTWAREINTERRUPTINSTRUCTION_H
