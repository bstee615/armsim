#ifndef COMPUTERWIDGET_H
#define COMPUTERWIDGET_H

#include "computer.h"
#include "observer.h"

class ComputerWidget: public Observer
{
protected:
    Computer *_computer;

public:
    void init(Computer *computer);

    virtual void update() {}
};

#endif // COMPUTERWIDGET_H
