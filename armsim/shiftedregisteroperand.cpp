#include "shiftedregisteroperand.h"
#include <QDebug>
#include "barrelshifter.h"

ShiftedRegisterOperand::ShiftedRegisterOperand(word w, Memory *_registers)
{
    registers = _registers;
    rMIndex = Memory::ExtractBits(w, 0, 3);
    shiftType = (ShiftType)(Memory::ExtractBits(w, 5, 6) >> 5);
}

word ShiftedRegisterOperand::shiftTypeToMethod(word w, word numShifts, ShiftedRegisterOperand::ShiftType shiftType)
{
    switch (shiftType) {
    case lsl:
        return BarrelShifter::lsl(w, numShifts);
    case lsr:
        return BarrelShifter::lsr(w, numShifts);
    case asr:
        return BarrelShifter::asr(w, numShifts);
    case ror:
        return BarrelShifter::ror(w, numShifts);
    }
}

const char* const ShiftedRegisterOperand::ShiftTypeToString [4] = {
    "lsl",
    "lsr",
    "asr",
    "ror"
};
