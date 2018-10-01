#ifndef IMMEDIATEOPERAND_H
#define IMMEDIATEOPERAND_H

#include "instructionoperand.h"
#include "memorytypes.h"

class RotatedImmediateOperand : public InstructionOperand
{
    word immediate;
    byte rotate;

public:
    RotatedImmediateOperand(word encodedWord);

    int value();
    QString toString();
};

#endif // IMMEDIATEOPERAND_H
