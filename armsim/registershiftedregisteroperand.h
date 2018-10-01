#ifndef REGISTERSHIFTEDREGISTEROPERAND_H
#define REGISTERSHIFTEDREGISTEROPERAND_H

#include <QString>
#include "shiftedregisteroperand.h"
#include "memorytypes.h"

class RegisterShiftedRegisterOperand : public ShiftedRegisterOperand
{
    byte rSIndex;

public:
    RegisterShiftedRegisterOperand(word w);

    QString toString();
    int value();
};

#endif // REGISTERSHIFTEDREGISTEROPERAND_H
