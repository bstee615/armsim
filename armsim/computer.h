#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu.h"
#include "loader.h"
#include "filewriter.h"
#include <QCoreApplication>
#include <QSet>
#include "instructions/softwareinterruptinstruction.h"
#include "ooutputdevice.h"

// To be thrown as a general error when loading a file
// so that the UI can display "None" instead of the invalid filename.
struct ErrorLoadingFile : public std::exception
{
    const char * what () const noexcept
    {
        return "Error loading file";
    }
};

class Computer: public FileWriter
{
    void logTrace(word pc);

public:
    CPU cpu;
    Memory ram;
    QSet<address> breakpoints;
    unsigned long long instructionCounter;
    OOutputDevice *outputDevice;

    bool IRQ = false; // Flag for whether the CPU should enter interrupt handling at the end of the current fetch-decode-execute cycle.

    bool traceAll = false;

    Computer(address numBytes);
    void loadFile(QString path);

    // Calls the CPU's fetch(), decode(), and execute() in a loop, until fetch() returns a 0.
    void run(bool *shouldStop);
    // Call the CPU's fetch(), decode(), and execute() methods once.
    int step();

    void toggleBreakpoint(address addr);
    bool isBreakpoint(address addr);

    void handleInputCharacter(char data);
};

#endif // COMPUTER_H
