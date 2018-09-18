#include "stackwidget.h"
#include "ui_stackwidget.h"
#include <QtMath>

StackWidget::StackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackWidget)
{
    ui->setupUi(this);
}

StackWidget::~StackWidget()
{
    delete ui;
}

void StackWidget::updateStackDisplay()
{
    word topOfStack = _computer->cpu.getGeneralRegister(13);
    address numberOfWords = qMin<address>(16, topOfStack / 4);

    QString str = "";
    for (address i = 0; i <= numberOfWords; i ++) {
        address addr = topOfStack - i*4;
        str += QString("%1").arg(addr, 8, 16, QChar('0')).prepend("0x") +
                QString("=") +
                QString("%1").arg(_computer->cpu.getRAM()->ReadWord(addr), 8, 16, QChar('0')).prepend("0x") +
                QString("\r\n");
    }

    ui->textareaStack->setText(str);
}
