#include "outputdevice.h"

void OutputDevice::notifyObservers()
{
    emit dataReceived();
}
