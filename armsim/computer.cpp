#include "computer.h"
#include "instructions/softwareinterruptinstruction.h"
#include <QDebug>

Computer::Computer(address numBytes)
{
    ram = Memory(numBytes);
    cpu = CPU(&ram);
    instructionCounter = 1;
    outputDevice = std::queue<char>();
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
    while (!(*shouldStop) && step() > 0)
    {

    }
}

int Computer::step()
{
    Instruction *i;
    word w, pc;

    try {
        w = cpu.fetch();
        pc = cpu.getProgramCounter();
        i = cpu.decode(w);
        if (i == nullptr) {
            qCritical() << "Computer:" << "Tried to execute unrecognized instruction.";
        }
        cpu.incrementPC();
        if (i->shouldExecute()) {
            cpu.execute(i);
        }
        /*
        if (i != nullptr) qDebug() << "Computer:" << QString("trace step %1: %2 executing instruction %3 at address %4: %5").arg(
                                          QString::number(instructionCounter),
                                          i->shouldExecute() ? "" : "not",
                                          QString::number(w, 16).prepend("0x"),
                                          QString::number(pc-8, 16).prepend("0x"),
                                          i->toString());
                                          */
    }
    catch (OutOfBoundsException ex) {
        return -1;
    }

    logTrace(pc-8);
    instructionCounter ++;

    if (ram.outputData != nullptr) {
        outputDevice.push(*ram.outputData);
    }

    SoftwareInterruptInstruction *swi = dynamic_cast<SoftwareInterruptInstruction*>(i);
    if (swi != nullptr) {
        if (swi->interruptCode == 0x11) {
            qDebug() << "Computer:" << "Encountered SWI 0x11. Stopping execution.";
            return 0;
        }
    }

    if (IRQ && cpu.getRegisters()->getIRQ()) {
        cpu.getRegisters()->processException(ProcessorMode::IRQ, 0x18);
        IRQ = false;
    }

    if (isBreakpoint(cpu.getProgramCounter() - 8)) {
        return 0;
    }

    return 1;
}

QString formattedNumber(unsigned int num, const char *fmt = "%1", int numDigits = 8, int base = 16)
{
    return QString(fmt).arg(num, numDigits, base, QChar('0')).append(" ").toUpper();
}

void Computer::logTrace(word pc)
{
    if (!isTracing()) return;

    QTextStream &writer = *writeMessage();

    writer << formattedNumber(instructionCounter, "%1", 6, 10)
           << formattedNumber(pc)
           << formattedNumber(cpu.getChecksum())
           << formattedNumber(cpu.getNZCF(), "%1", 4, 2)
           << "SYS "; // TODO: Replace this when implementing CPU mode.

    for (unsigned int i = 0; i <= 14; i ++) {
        QString fmt("%1=~"); // This will end up in as "r<i>=<contents of ri>"
        fmt = fmt.arg(i).replace("~", "%1");
        fmt = formattedNumber(cpu.getGeneralRegister(i), fmt.toStdString().c_str());
//        if (i == 14) fmt = fmt.trimmed();
        writer << fmt;
    }

    writer << "\n";
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

void Computer::handleInputCharacter(char data)
{
    ram.inputData = new char(data);
    IRQ = true;
}

char *Computer::getOutputCharacter()
{
    if (outputDevice.empty()) {
        return nullptr;
    }
    else {
        char *ret = new char(outputDevice.front());
        outputDevice.pop();
        return ret;
    }
}
