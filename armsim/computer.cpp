#include "computer.h"
#include "softwareinterruptinstruction.h"
#include <QDebug>

Computer::Computer(address numBytes)
{
    ram = Memory(numBytes);
    cpu = CPU(&ram);
    instructionCounter = 1;
}

void Computer::loadFile(QString path)
{
    if (path.isEmpty()) {
        return;
    }

    if (!loadELF(path, &cpu)) {
        throw ErrorLoadingFile();
        return;
    }

    instructionCounter = 1;
}

void Computer::run(bool *shouldStop)
{
    const word halt = 0;
    while (!(*shouldStop) && step() != halt && !breakpoints.contains(cpu.getProgramCounter()))
    {
        // Do nothing for now.
    }
}

word Computer::step()
{
    word w = cpu.fetch();
    word pc = cpu.getProgramCounter();
    if (w == 0) return w;
    Instruction *i = cpu.decode(w);
    cpu.incrementPC();
    cpu.execute(i);

    logTrace(pc);
    instructionCounter ++;

    if (dynamic_cast<SoftwareInterruptInstruction*>(i) != nullptr) {
        return 0;
    }

    return w;
}

QString formattedNumber(unsigned int num, const char *fmt = "%1", int numDigits = 8, int base = 16)
{
    return QString(fmt).arg(num, numDigits, base, QChar('0')).toUpper();
}

void Computer::logTrace(word pc)
{
    if (!isTracing()) return;

    QTextStream &writer = *writeMessage();

    writer << formattedNumber(instructionCounter, "%1", 6, 10)
           << formattedNumber(pc).prepend(" ")
           << formattedNumber(cpu.getChecksum()).prepend(" ")
           << formattedNumber(cpu.getNZCF(), "%1", 4).prepend(" ")
           << " SYS"; // TODO: Replace this when implementing CPU mode.

    for (unsigned int i = 0; i <= 14; i ++) {
        QString fmt("%1=~"); // This will end up in as "r<i>=<contents of ri>"
        fmt = fmt.arg(i).replace("~", "%1");

        writer << formattedNumber(cpu.getGeneralRegister(i), fmt.toStdString().c_str()).prepend(" ");
    }

    writer << "\r\n";
    writer.flush();
}

bool Computer::isBreakpoint(address addr)
{
    return breakpoints.contains(addr);
}

void Computer::toggleBreakpoint(address addr)
{
    if (isBreakpoint(addr)) {
        breakpoints.remove(addr);
    }
    else {
        breakpoints.insert(addr);
    }
}

void Computer::toggleBreakpointAtCurrentInstruction()
{
    toggleBreakpoint(cpu.getProgramCounter());
}
