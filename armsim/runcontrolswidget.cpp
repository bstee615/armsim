#include "runcontrolswidget.h"
#include "ui_runcontrolswidget.h"

RunControlsWidget::RunControlsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunControlsWidget)
{
    ui->setupUi(this);

    setRunningState(false);
    updateUIToRunningState();
}

RunControlsWidget::~RunControlsWidget()
{
    delete runningThread;
    delete ui;
}

void RunControlsWidget::on_btnRun_clicked()
{
    startComputerThread(new ComputerRunThread(_computer));
}

void RunControlsWidget::on_btnStep_clicked()
{
    startComputerThread(new ComputerStepThread(_computer));
}

void RunControlsWidget::on_btnStop_clicked()
{
    stopComputerThread(runningThread);
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
    ui->btnStop->setEnabled(isRunning);
}

void RunControlsWidget::deleteRunningComputerThread()
{
    delete runningThread;
    runningThread = nullptr;
    setRunningState(false);
    updateUIToRunningState();
}

void RunControlsWidget::startComputerThread(ComputerThread *computerThread)
{
    setRunningState(true);
    updateUIToRunningState();

    if (runningThread != nullptr) {
        delete runningThread;
    }
    runningThread = computerThread;
    runningThread->start();
    connect(runningThread, SIGNAL(finished()), this, SLOT(updateUIToRunningState()));
}

void RunControlsWidget::stopComputerThread(ComputerThread *computerThread)
{
    runningThread->stopRunning();
    connect(runningThread, SIGNAL(finished()), this, SLOT(deleteRunningComputerThread()));
}
