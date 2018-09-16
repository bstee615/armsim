#ifndef OCOMPUTER_H
#define OCOMPUTER_H

#include <vector>
#include "observer.h"

class OComputer
{
protected:
    std::vector<Observer *> observers;
    void notifyObservers();

public:
    void registerObserver(Observer *o);
};

#endif // OCOMPUTER_H
