/* registershiftedregisteroperand.h
 * Models an addressing mode where the offset is a register's value shifted by another register's value.
*/

#ifndef REGISTERSHIFTEDREGISTEROPERAND_H
#define REGISTERSHIFTEDREGISTEROPERAND_H

#include <QString>
#include "shiftedregisteroperand.h"
#include "memorytypes.h"
#include "registermemory.h"

class RegisterShiftedRegisterOperand : public ShiftedRegisterOperand
{
    byte rSIndex; // Index of the shift register from 0-15
    word rSValue;

public:
    RegisterShiftedRegisterOperand(word w, RegisterMemory *_registers);

    QString toString() override;
    int value() override;
};

#endif // REGISTERSHIFTEDREGISTEROPERAND_H
