#include "runcontrolswidget.h"
#include "ui_runcontrolswidget.h"

RunControlsWidget::RunControlsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunControlsWidget)
{
    ui->setupUi(this);
}

RunControlsWidget::~RunControlsWidget()
{
    delete ui;
}

void RunControlsWidget::on_btnRun_clicked()
{
    // TODO: Run loaded program.
}

void RunControlsWidget::on_btnStep_clicked()
{
    word w = _computer->step();
    qDebug() << "Step:" << "Executed instruction" << w;
}
