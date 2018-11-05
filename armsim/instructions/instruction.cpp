#include "instruction.h"

const char * const Instruction::ConditionCodeToString [16] = {
    "eq", "ne", "cs", "cc", "mi", "pl", "vs", "vc", "hi", "ls", "ge", "lt", "gt", "le", "", "XX" // XX for unpredictable
};

Instruction::Instruction(word w, RegisterMemory *_registers)
{
    cond = Memory::ExtractBits(w, 28, 31) >> 28;
    registers = _registers;
}

bool Instruction::shouldExecute()
{
    switch ((ConditionCode)cond) {
    case EQ:
        return flagIsSet(NZCFFlag::Zero);
    case NE:
        return !flagIsSet(NZCFFlag::Zero);
    case CS:
        return flagIsSet(NZCFFlag::Carry);
    case CC:
        return !flagIsSet(NZCFFlag::Carry);
    case MI:
        return flagIsSet(NZCFFlag::Negative);
    case PL:
        return !flagIsSet(NZCFFlag::Negative);
    case VS:
        return flagIsSet(NZCFFlag::Overflow);
    case VC:
        return !flagIsSet(NZCFFlag::Overflow);
    case HI:
        return flagIsSet(NZCFFlag::Carry) && !flagIsSet(NZCFFlag::Zero);
    case LS:
        return !flagIsSet(NZCFFlag::Carry) || flagIsSet(NZCFFlag::Zero);
    case GE:
        return flagIsSet(NZCFFlag::Negative) == flagIsSet(NZCFFlag::Overflow);
    case LT:
        return flagIsSet(NZCFFlag::Negative) != flagIsSet(NZCFFlag::Overflow);
    case GT:
        return !flagIsSet(NZCFFlag::Zero) && flagIsSet(NZCFFlag::Negative) == flagIsSet(NZCFFlag::Overflow);
    case LE:
        return flagIsSet(NZCFFlag::Zero) || flagIsSet(NZCFFlag::Negative) != flagIsSet(NZCFFlag::Overflow);
    case AL:
        return true;
    default:
        return false;
    break;
    }
}

bool Instruction::flagIsSet(NZCFFlag flag)
{
    return registers->TestFlag(CPSR_OFFSET, flag);
}
