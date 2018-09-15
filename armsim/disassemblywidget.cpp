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
