/* immediateshiftedregisteroperand.h
 * Models an addressing mode where the offset is a register's value shifted by a 5-bit immediate.
*/

#ifndef IMMEDIATESHIFTEDREGISTEROPERAND_H
#define IMMEDIATESHIFTEDREGISTEROPERAND_H

#include <QString>
#include "shiftedregisteroperand.h"

class ImmediateShiftedRegisterOperand : public ShiftedRegisterOperand
{
    byte immediateShift; // The 5-bit shift magnitude

public:
    ImmediateShiftedRegisterOperand(word w, RegisterMemory *registers);

    QString toString() override;
    int value() override;
};

#endif // IMMEDIATESHIFTEDREGISTEROPERAND_H
