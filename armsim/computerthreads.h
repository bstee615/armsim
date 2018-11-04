#ifndef COMPUTERTHREADS_H
#define COMPUTERTHREADS_H

#include "computer.h"
#include <QThread>

class ComputerThread: public QThread
{
    Q_OBJECT
    virtual void run() = 0;

protected:
    Computer *_computer = nullptr;
    bool shouldStop = false;

public:
    void stopRunning() { shouldStop = true; }
    char *getOutputCharacter() {
        return _computer->getOutputCharacter();
    }
};

class ComputerRunThread : public ComputerThread
{
    Q_OBJECT

    void run() {
        _computer->run(&shouldStop);
    }

public:
    ComputerRunThread(Computer *computer) { _computer = computer; }
};

class ComputerStepThread : public ComputerThread
{
    Q_OBJECT

    void run() { _computer->step(); }

public:
    ComputerStepThread(Computer *computer) { _computer = computer; }
};

#endif // COMPUTERTHREADS_H
