#include "computer.h"

Computer::Computer(address numBytes)
{
    ram = Memory(numBytes);
    cpu = CPU(&ram);
    instructionCounter = 0;
}

void Computer::loadFile(QString path)
{
    if (path.isEmpty()) {
        return;
    }

    if (!loadELF(path, &cpu)) {
        qCritical() << "Error:" << "Exiting application.";
        QCoreApplication::exit(1);
        exit(1);
    }

    instructionCounter = 0;
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
    cpu.decode(w);
    cpu.execute();

    qDebug() << "Computer:" << "Instruction count" << instructionCounter << "Executed word" << QString("%1").arg(w, 8, 16, QChar('0')).toUpper().prepend(QString("0x"));
    logTrace();
    instructionCounter ++;

    return w;
}

QString formattedNumber(unsigned int num, const char *fmt = "%1", int numDigits = 8)
{
    return QString(fmt).arg(num, numDigits, 10, QChar('0')).append(" ");
}

void Computer::logTrace()
{
    if (!isTracing()) return;

    QTextStream &writer = *writeMessage();

    writer << formattedNumber(instructionCounter, "%1", 6)
           << formattedNumber(cpu.getProgramCounter())
           << formattedNumber(cpu.getChecksum())
           << formattedNumber(cpu.getNZSF(), "%1", 4)
           << "SYS "; // TODO: Replace this when implementing CPU mode.

    for (unsigned int i = 0; i <= 11; i ++) {
        QString fmt("r%1=~"); // This will end up in as "r<i>=<contents of ri>"
        fmt = fmt.arg(i).replace("~", "%1");

        writer << formattedNumber(cpu.getGeneralRegister(i), fmt.toStdString().c_str());
    }

    writer << "\r\n";
}

bool Computer::isBreakpoint(address addr)
{
    return breakpoints.contains(addr);
}

void Computer::addBreakpoint(address addr)
{
    breakpoints.insert(addr);
}
