#include "memorywidget.h"
#include "ui_memorywidget.h"

MemoryWidget::MemoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryWidget)
{
    ui->setupUi(this);
}

MemoryWidget::~MemoryWidget()
{
    delete ui;
}

void MemoryWidget::updateMemoryDisplay()
{
    const address rowLength = 16;

    QStringList addressedBytes;
    address pc = _computer->cpu.getProgramCounter();
    for (address row_i = 0; row_i < 10; row_i ++) {
        address rowAddress = pc + (row_i * rowLength);
        addressedBytes << QString("%1").arg(rowAddress, 8, 16, QChar('0')).prepend("0x") << " ";

        QStringList endOfLine;
        for (address address_i = 0; address_i < rowLength; address_i ++) {
            byte b = _computer->cpu.getRAM()->ReadByte(rowAddress + address_i);
            addressedBytes << QString("%1").arg(b, 2, 16, QChar('0')) << " ";
            endOfLine << QChar((char)b);
        }
        addressedBytes << "\t" << endOfLine << "\r\n";
    }

    ui->textareaMemory->setText(addressedBytes.join(""));
}
