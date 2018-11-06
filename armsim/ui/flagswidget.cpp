#include "flagswidget.h"
#include "ui_flagswidget.h"

static char const * ProcessorModeToString[] = {
    "User", "System", "Supervisor", "Monitor", "Abort", "Undefined", "FIQ", "IRQ", "Unknown processor mode."
};

FlagsWidget::FlagsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlagsWidget)
{
    ui->setupUi(this);

    ui->tblFlags->setHorizontalHeaderLabels(QStringList() << "N" << "Z" << "C" << "F" << "IRQ");
}

FlagsWidget::~FlagsWidget()
{
    delete ui;
}

void FlagsWidget::updateFlags()
{
    NZCFFlag flags[] = { NZCFFlag::Negative, NZCFFlag::Zero, NZCFFlag::Carry, NZCFFlag::Overflow };
    for (int i = 0; i < 4; i ++) {
        NZCFFlag flag = flags[i];
        ui->tblFlags->setItem(0, i, new QTableWidgetItem(QString::number(_computer->cpu.getRegisters()->getNZCF(flag) ? 1 : 0)));
    }
    ui->tblFlags->setItem(0, 4, new QTableWidgetItem(QString::number(_computer->cpu.getRegisters()->getIRQ())));

    // IRQ Mode
    ui->processorMode->setText(QString(ProcessorModeToString[_computer->cpu.getRegisters()->getProcessorMode()]));
}

void FlagsWidget::init(Computer *computer)
{
    ComputerWidget::init(computer);
    updateFlags();
}
