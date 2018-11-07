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
    RegisterMemory *regs = _computer->cpu.getRegisters();
    QString str = "";
    for (int i = 0; i <= 11; i ++) {
        str += formatRegisterValue(QString("r") + QString::number(i), regs->getRegisterValue(i));
    }
    str += formatRegisterValue(QString("IP"), regs->getRegisterValue(12));
    str += formatRegisterValue(QString("SP"), regs->getRegisterValue(13));
    str += formatRegisterValue(QString("LR"), regs->getRegisterValue(14));
    str += formatRegisterValue(QString("PC"), regs->getRegisterValue(15));
    ui->textareaRegisters->setText(str);
}
