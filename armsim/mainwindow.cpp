#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options &options, QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::MainWindow),
    _options(options),
    computer(Computer(_options.getMemory(), _options.getFilename()))
{
    ui->setupUi(this);
    ui->runControlsWidget->init(&computer);
    ui->loaderWidget->init(&computer);
    ui->loaderWidget->setFileDialogText(_options.getFilename());

    ui->runControlsWidget->setRunningState(false);
    connect(ui->runControlsWidget->btnRun, SIGNAL(clicked(bool)), this, SLOT(startComputerRunThread()));
    connect(ui->runControlsWidget->btnStep, SIGNAL(clicked(bool)), this, SLOT(startComputerStepThread()));
    connect(ui->runControlsWidget->btnStop, SIGNAL(clicked(bool)), this, SLOT(stopComputerThread()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startComputerRunThread()
{
    setComputerThread(new ComputerRunThread(&computer));
}

void MainWindow::startComputerStepThread()
{
    setComputerThread(new ComputerStepThread(&computer));
}

void MainWindow::setComputerThread(ComputerThread *computerThread)
{
    ui->runControlsWidget->setRunningState(true);

    if (runningThread != nullptr) {
        delete runningThread;
    }
    runningThread = computerThread;
    connect(runningThread, SIGNAL(finished()), this, SLOT(deleteComputerThread()));
    runningThread->start();
}

void MainWindow::stopComputerThread()
{
    runningThread->stopRunning();
}

void MainWindow::deleteComputerThread()
{
    delete runningThread;
    runningThread = nullptr;

    ui->runControlsWidget->setRunningState(false);
}
