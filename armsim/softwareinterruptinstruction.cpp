#include "softwareinterruptinstruction.h"
#include <QDebug>

SoftwareInterruptInstruction::SoftwareInterruptInstruction(word w)
{
    // interruptCode := w;
}

QString SoftwareInterruptInstruction::toString()
{
    return "SoftwareInterruptInstruction: Not implemented.";
}

void SoftwareInterruptInstruction::execute()
{
    qDebug() << "swi: noop";
}
