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
    delete runningThread;
    delete ui;
}

void RunControlsWidget::on_btnRun_clicked()
{
    // TODO: Run loaded program.
}

void RunControlsWidget::on_btnStep_clicked()
{
    setRunningState(true);
    updateUIToRunningState();

    if (runningThread != nullptr) {
        delete runningThread;
    }
    runningThread = new ComputerStepThread(_computer);
    runningThread->start();
    connect(runningThread, SIGNAL(finished()), this, SLOT(updateUIToRunningState()));
}

void RunControlsWidget::update()
{
    setRunningState(false);
}

void RunControlsWidget::setRunningState(bool running)
{
    isRunning = running;
}

void RunControlsWidget::updateUIToRunningState()
{
    ui->btnRun->setEnabled(!isRunning);
    ui->btnStep->setEnabled(!isRunning);
}
