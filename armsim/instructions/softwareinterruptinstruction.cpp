#include "softwareinterruptinstruction.h"
#include "memory.h"
#include <QDebug>

SoftwareInterruptInstruction::SoftwareInterruptInstruction(word w)
{
     interruptCode = Memory::ExtractBits(w, 0, 23);
}

QString SoftwareInterruptInstruction::toString()
{
    return QString("swi %1").arg(QString::number(interruptCode));
}

void SoftwareInterruptInstruction::execute()
{
}
