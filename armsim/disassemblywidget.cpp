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

QString listItemText(address address, word instruction, QString instructionText, bool bp)
{
    return QString("%4\t%1\t%2\t%3").arg(to8DigitHex(address),
                                     to8DigitHex(instruction),
                                     instructionText,
                                     (bp ? QString("+") : QString("")));
}

const QString dummyASMInstructions[] = { "add fp, sp, #0","sub sp, sp, #12","str r0, [fp, #-8]","add sp, fp, #0","ldmfd sp!, {fp}","bx lr","push {fp}","add fp, sp, #0",
                                     "sub sp, sp, #12","str r0, [fp, #-8]","add sp, fp, #0","ldmfd sp!, {fp}","bx lr","push {fp, lr}","add fp, sp, #4","sub sp, sp, #8","mov r3, #10",
                                     "str r3, [fp, #-8]","mov r3, #0","str r3, [fp, #-12]","b 174 <mystart+0x3c>","ldr r2, [fp, #-12]","ldr r3, [fp, #-8]",
                                     "add r3, r2, r3","str r3, [fp, #-12]","ldr r3, [fp, #-8]","sub r3, r3, #1","str r3, [fp, #-8]","ldr r3, [fp, #-8]",
                                     "cmp r3, #0","bne 158 <mystart+0x20>","ldr r0, [fp, #-12]","bl 100 <putc>","ldr r3, [pc, #28]","ldr r3, [r3]","mov r0, r3",
                                     "bl 11c <puts>","ldr r3, [fp, #-12]","mov r0, r3","sub sp, fp, #4","pop {fp, lr}","bx" };

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
        auto item = new QListWidgetItem(listItemText(addr, instruction, dummyASMInstructions[offset+rowPadding], bp), ui->listDisassembly);
        if (offset == 0) item->setBackgroundColor(QColor(255, 100, 100));
        ui->listDisassembly->addItem(item);
    }
}
