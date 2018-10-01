#ifndef IMMEDIATESHIFTEDREGISTEROPERAND_H
#define IMMEDIATESHIFTEDREGISTEROPERAND_H

#include <QString>
#include "shiftedregisteroperand.h"

class ImmediateShiftedRegisterOperand : public ShiftedRegisterOperand
{
    word immediateShift;

public:
    ImmediateShiftedRegisterOperand(word w, Memory *registers);

    QString toString();
    int value();
};

#endif // IMMEDIATESHIFTEDREGISTEROPERAND_H
