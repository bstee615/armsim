#ifndef COMPUTERWIDGET_H
#define COMPUTERWIDGET_H

#include "computer.h"

class ComputerWidget
{
protected:
    Computer *_computer;

public:
    virtual void init(Computer *computer);
};

#endif // COMPUTERWIDGET_H
