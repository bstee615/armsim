/* immediateoperand.h
 * Models an immediate instruction offset operand.
*/

#ifndef IMMEDIATEOPERAND_H
#define IMMEDIATEOPERAND_H

#include <QString>
#include "instructionoperand.h"
#include "memorytypes.h"

class ImmediateOperand : public InstructionOperand
{
    word immediate; // Immediate offset

public:
    ImmediateOperand(word w);

    QString toString();
    int value();
};

#endif // IMMEDIATEOPERAND_H
