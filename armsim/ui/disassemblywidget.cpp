#include "disassemblywidget.h"
#include "ui_disassemblywidget.h"
#include <QtMath>
#include "instructionfactory.h"

DisassemblyWidget::DisassemblyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisassemblyWidget)
{
    ui->setupUi(this);
}

DisassemblyWidget::~DisassemblyWidget()
{
    delete ui;
}

QString to8DigitHex(word num)
{
    return QString("%1").arg(num, 8, 16, QChar('0')).toUpper().prepend(QString("0x")); // Format: 0x0F1BADEE
}

QString listItemText(address address, word instruction, QString instructionText, bool bp)
{
    return QString("%4\t%1\t%2\t%3").arg(to8DigitHex(address),
                                     to8DigitHex(instruction),
                                     instructionText,
                                     (bp ? QString("+") : QString("")));
}

void DisassemblyWidget::updateDisassemblyText()
{
    ui->listDisassembly->clear();

    Memory &ram = _computer->ram;
    address pc = _computer->cpu.getProgramCounter();
    const int rowPadding = 6;
    for (int offset = -rowPadding; offset <= rowPadding; offset ++) {
        int signedAddress = pc + (offset*4);
        if (signedAddress < 0) continue;

        address addr = signedAddress;
        word instruction = ram.ReadWord(addr);
        bool bp = _computer->isBreakpoint(addr);
        QString disassembly = InstructionFactory::getDecodedInstruction(instruction, _computer->cpu.getRAM(), _computer->cpu.getRegisters())->toString();
        auto item = new QListWidgetItem(listItemText(addr, instruction, disassembly, bp), ui->listDisassembly);
        if (offset == 0) item->setBackgroundColor(QColor(255, 100, 100));
        ui->listDisassembly->addItem(item);
    }
}
