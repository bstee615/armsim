#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu.h"
#include "loader.h"
#include "filewriter.h"
#include <QCoreApplication>
#include <QSet>

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
public:
    CPU cpu;
    Memory ram;
    QSet<address> breakpoints;
    unsigned long long instructionCounter;

    Computer(address numBytes);
    void loadFile(QString path);

    // Calls the CPU's fetch(), decode(), and execute() in a loop, until fetch() returns a 0.
    void run(bool *shouldStop);
    // Call the CPU's fetch(), decode(), and execute() methods once.
    word step();

    void logTrace();

    bool isBreakpoint(address addr);
    void toggleBreakpoint(address addr);
    void toggleBreakpointAtCurrentInstruction();
};

#endif // COMPUTER_H
