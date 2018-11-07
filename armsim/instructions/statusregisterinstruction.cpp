#include "statusregisterinstruction.h"
#include "rotatedimmediateoperand.h"
#include "registeroffsetoperand.h"

StatusRegisterInstruction::StatusRegisterInstruction(word w, RegisterMemory *_registers): Instruction(w, _registers)
{
    R = Memory::ExtractBits(w, 22, 22) != 0;

    MRS = Memory::ExtractBits(w, 20, 21) >> 20 == 0b00;
    if (MRS) { // MRS
        rDIndex = Memory::ExtractBits(w, 12, 15) >> 12;
    }
    else { // MSR
        fieldMask = Memory::ExtractBits(w, 16, 19) >> 16;
        if (Memory::ExtractBits(w, 25, 25) != 0) {
            addressingMode = new RotatedImmediateOperand(w);
        }
        else {
            addressingMode = new RegisterOffsetOperand(w, _registers);
        }
    }
}

QString StatusRegisterInstruction::toString()
{
    if (MRS) {
        return QString("mrs r%1, %2").arg(QString::number(rDIndex),
                                          R ? QString("spsr") : QString("cpsr"));
    }
    else {
        return QString("msr %1, %2").arg(R ? QString("spsr") : QString("cpsr"),
                                         addressingMode->toString());
    }
}

void StatusRegisterInstruction::execute()
{
    if (MRS) {
        word val = R ? registers->getSPSR() : registers->getCPSR();
        registers->setRegisterValue(rDIndex, val);
    }
    else {
        word val = addressingMode->value();
        word mask = 0;
        if (Memory::ExtractBits(fieldMask, 0, 0) != 0) mask = mask | 0x000000FF;
        if (Memory::ExtractBits(fieldMask, 1, 1) != 0) mask = mask | 0x0000FF00;
        if (Memory::ExtractBits(fieldMask, 2, 2) != 0) mask = mask | 0x00FF0000;
        if (Memory::ExtractBits(fieldMask, 3, 3) != 0) mask = mask | 0xFF000000;

        word psr = R ? registers->getSPSR() : registers->getCPSR();
        psr = (psr & ~mask) | (val & mask);
        R ? registers->setSPSR(psr) : registers->setCPSR(psr);
    }
}
