#include "memorywidget.h"
#include "ui_memorywidget.h"

MemoryWidget::MemoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryWidget)
{
    ui->setupUi(this);
    connect(ui->hexspinStartingAddress, SIGNAL(returnPressed()), this, SLOT(on_btnEnterStartingAddress_clicked()));
}

MemoryWidget::~MemoryWidget()
{
    delete ui;
}

void MemoryWidget::updateMemoryDisplay()
{
    updateMemoryDisplay(ui->hexspinStartingAddress->hexValue());
}

void MemoryWidget::updateMemoryDisplay(address startingAddress)
{
    const address numRows = 16;
    const address rowLength = 16;

    QStringList addressedBytes;
    address pc = startingAddress;
    for (address row_i = 0; row_i < numRows; row_i ++) {
        address rowAddress = pc + (row_i * rowLength);
        addressedBytes << QString("%1").arg(rowAddress, 8, 16, QChar('0')).prepend("0x") << " ";

        QStringList endOfLine;
        for (address address_i = 0; address_i < rowLength; address_i ++) {
            byte b = _computer->cpu.getRAM()->ReadByte(rowAddress + address_i);
            addressedBytes << QString("%1").arg(b, 2, 16, QChar('0')) << " ";

            QChar toChar = QChar((char)b);
            if (b == 0) toChar = QChar('.');
            endOfLine << toChar;
        }
        QString endOfLineString = endOfLine.join("");
        endOfLineString.replace(' ', '.');
        endOfLineString.replace('\r', '.');
        endOfLineString.replace('\n', '.');
        endOfLineString.replace('\t', '.');
        addressedBytes << "\t" << endOfLineString << "\r\n";
    }

    ui->textareaMemory->setText(addressedBytes.join(""));
}

void MemoryWidget::setStartingAddress(address startingAddress)
{
    ui->hexspinStartingAddress->setHexValue(startingAddress);
    updateMemoryDisplay();
}

void MemoryWidget::on_btnEnterStartingAddress_clicked()
{
    updateMemoryDisplay();
}
