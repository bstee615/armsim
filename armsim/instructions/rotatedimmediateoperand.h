/* rotatedimmediateoperand.h
 * Models an addressing mode where the offset is an 8-bit immediate rotated right by 2*[a 4-bit immediate]
*/

#ifndef IMMEDIATEOPERAND_H
#define IMMEDIATEOPERAND_H

#include "instructionoperand.h"
#include "memorytypes.h"

class RotatedImmediateOperand : public InstructionOperand
{
    byte immediate; // 8-bit immediate
    byte rotate; // Half the number of rotations

public:
    RotatedImmediateOperand(word encodedWord);

    int value() override;
    QString toString() override;
};

#endif // IMMEDIATEOPERAND_H
