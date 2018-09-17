#include "runcontrolswidget.h"
#include "ui_runcontrolswidget.h"

RunControlsWidget::RunControlsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunControlsWidget)
{
    ui->setupUi(this);

    btnRun = ui->btnRun;
    btnStep = ui->btnStep;
    btnStop = ui->btnStop;
}

RunControlsWidget::~RunControlsWidget()
{
    delete ui;
}

void RunControlsWidget::setRunningState(bool running)
{
    ui->btnRun->setEnabled(!running);
    ui->btnStep->setEnabled(!running);
    ui->btnStop->setEnabled(running);
}

void RunControlsWidget::on_btnRun_clicked()
{
    setRunningState(true);
}

void RunControlsWidget::on_btnStep_clicked()
{
    setRunningState(true);
}

void RunControlsWidget::on_btnStop_clicked()
{
    setRunningState(false);
}
