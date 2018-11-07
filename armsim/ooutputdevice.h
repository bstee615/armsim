#ifndef OOUTPUTDEVICE_H
#define OOUTPUTDEVICE_H

// Abstract Observer class for the Computer's output device.
class OOutputDevice
{
public:
    char *outputData;
    virtual void notifyObservers() = 0;
};

#endif // OOUTPUTDEVICE_H
