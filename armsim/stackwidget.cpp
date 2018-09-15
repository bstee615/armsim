#include "stackwidget.h"
#include "ui_stackwidget.h"

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
