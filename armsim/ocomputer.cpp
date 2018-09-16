#include "ocomputer.h"

void OComputer::notifyObservers()
{
    for (Observer *o : observers) {
        o->update();
    }
}

void OComputer::registerObserver(Observer *o)
{
    observers.push_back(o);
}
