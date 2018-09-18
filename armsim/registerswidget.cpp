#include "registerswidget.h"
#include "ui_registerswidget.h"
#include <QDebug>

RegistersWidget::RegistersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistersWidget)
{
    ui->setupUi(this);
}

RegistersWidget::~RegistersWidget()
{
    delete ui;
}

QString formatRegisterValue(QString registerName, word registerValue)
{
    return QString("%1").arg(registerValue, 8, 16, QChar('0')).prepend("0x").append("\r\n").prepend(registerName + "=");
}

void RegistersWidget::updateRegisters()
{
    Memory *regs = _computer->cpu.getRegisters();
    QString str = "";
    for (int i = 0; i <= 11; i ++) {
        str += formatRegisterValue(QString("r") + QString::number(i), regs->ReadWord(R0_OFFSET + i*4));
    }
    str += formatRegisterValue(QString("IP"), regs->ReadWord(IP_OFFSET));
    str += formatRegisterValue(QString("SP"), regs->ReadWord(SP_OFFSET));
    str += formatRegisterValue(QString("LR"), regs->ReadWord(LR_OFFSET));
    str += formatRegisterValue(QString("PC"), regs->ReadWord(PC_OFFSET));
    ui->textareaRegisters->setText(str);
}
