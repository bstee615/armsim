#include "softwareinterruptinstruction.h"
#include "memory.h"
#include <QDebug>

SoftwareInterruptInstruction::SoftwareInterruptInstruction(word w)
{
     interruptCode = Memory::ExtractBits(w, 0, 23);
}

QString SoftwareInterruptInstruction::toString()
{
    return "SoftwareInterruptInstruction: Not implemented.";
}

void SoftwareInterruptInstruction::execute()
{
    qDebug() << "swi: noop";
}
