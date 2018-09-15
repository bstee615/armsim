#include "registerswidget.h"
#include "ui_registerswidget.h"

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
