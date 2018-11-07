#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include <QObject>
#include "ooutputdevice.h"
#include <queue>

// Omplementation of OOutputDevice.
class OutputDevice: public QObject, public OOutputDevice
{
    Q_OBJECT

public:
    void notifyObservers() override;

signals:
    dataReceived();
};

#endif // OUTPUTDEVICE_H
