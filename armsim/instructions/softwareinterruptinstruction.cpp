#include "softwareinterruptinstruction.h"
#include "memory.h"
#include <QDebug>

SoftwareInterruptInstruction::SoftwareInterruptInstruction(word w):
    Instruction(w, nullptr)
{
     interruptCode = Memory::ExtractBits(w, 0, 23);
}

QString SoftwareInterruptInstruction::toString()
{
    return QString("swi%1 %2").arg(CC_STR, QString::number(interruptCode));
}

void SoftwareInterruptInstruction::execute()
{
    // Computer handles 0x11 quit, others handled by armos
}
