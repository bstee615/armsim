#include "softwareinterruptinstruction.h"
#include "memory.h"
#include <QDebug>

SoftwareInterruptInstruction::SoftwareInterruptInstruction(word w, RegisterMemory *_registers):
    Instruction(w, _registers)
{
     interruptCode = Memory::ExtractBits(w, 0, 23);
     pcValue = registers->getRegisterValue(15);
}

QString SoftwareInterruptInstruction::toString()
{
    return QString("swi%1 %2").arg(CC_STR, QString::number(interruptCode));
}

void SoftwareInterruptInstruction::execute()
{
    // Computer handles 0x11 quit, others handled by armos
    if (interruptCode != 0x11) {
        // Switch to SVC and perform exception processing.
        registers->processException(ProcessorMode::Supervisor, 0x8);
    }
}
