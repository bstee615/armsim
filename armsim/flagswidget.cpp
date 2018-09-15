#include "flagswidget.h"
#include "ui_flagswidget.h"

FlagsWidget::FlagsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlagsWidget)
{
    ui->setupUi(this);
}

FlagsWidget::~FlagsWidget()
{
    delete ui;
}
