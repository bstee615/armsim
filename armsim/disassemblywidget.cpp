#include "disassemblywidget.h"
#include "ui_disassemblywidget.h"

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

QString listItemText(address address, word instruction, bool bp)
{
    return QString("%3\t%1\t%2").arg(to8DigitHex(address),
                                     to8DigitHex(instruction),
                                     (bp ? QString("+") : QString("")));
}

void DisassemblyWidget::updateDisassemblyText()
{
    ui->listDisassembly->clear();

    Memory &ram = _computer->ram;
    address pc = _computer->cpu.getProgramCounter();
    const int rowPadding = 3;
    for (int offset = -rowPadding; offset <= rowPadding; offset ++) {
        address addr = pc + (offset*4);
        word instruction = ram.ReadWord(addr);
        bool bp = _computer->isBreakpoint(addr);
        auto item = new QListWidgetItem(listItemText(addr, instruction, bp), ui->listDisassembly);
        if (offset == 0) item->setBackgroundColor(QColor(255, 100, 100));
        ui->listDisassembly->addItem(item);
    }
}
