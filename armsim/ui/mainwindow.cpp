#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "outputdevice.h"

MainWindow::MainWindow(Options &options, QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::MainWindow),
    _options(options),
    computer(new Computer(_options.memory))
{
    ui->setupUi(this);

    OutputDevice *outputDevice = new OutputDevice();
    computer->outputDevice = outputDevice;
    connect(outputDevice, SIGNAL(dataReceived()), ui->terminalWidget, SLOT(updateText()));
    computer->traceAll = options.traceAll;

    initComputerWidgets();
    ui->runControlsWidget->setRunningState(false);

    connect(ui->runControlsWidget->btnRun, SIGNAL(clicked(bool)), this, SLOT(startComputerRunThread()));
    connect(ui->runControlsWidget->btnStep, SIGNAL(clicked(bool)), this, SLOT(startComputerStepThread()));
    connect(ui->runControlsWidget->btnStop, SIGNAL(clicked(bool)), this, SLOT(stopComputerThread()));
    connect(ui->runControlsWidget, SIGNAL(toggledBreakpoint()), this, SLOT(updateAllUI()));
    connect(ui->loaderWidget, SIGNAL(loadedFile()), this, SLOT(updateAllUI()));

    ui->loaderWidget->loadFile(_options.filename);
    ui->memoryWidget->setStartingAddress(computer->cpu.getProgramCounter());

    ui->runControlsWidget->startTrace();
}

MainWindow::~MainWindow()
{
    delete computer;
    delete ui;
}

void MainWindow::runThenExit()
{
    startComputerRunThread();
    connect(runningThread, SIGNAL(finished()), this, SLOT(close()));
}

void MainWindow::startComputerRunThread()
{
    setComputerThread(new ComputerRunThread(computer));
}

void MainWindow::startComputerStepThread()
{
    setComputerThread(new ComputerStepThread(computer));
}

void MainWindow::setComputerThread(ComputerThread *computerThread)
{
    ui->runControlsWidget->setRunningState(true);
    ui->loaderWidget->setEnabled(false);

    if (runningThread != nullptr) {
        delete runningThread;
    }
    runningThread = computerThread;
    connect(runningThread, SIGNAL(finished()), this, SLOT(deleteComputerThread()));
    connect(runningThread, SIGNAL(finished()), this, SLOT(updateAllUI()));
    runningThread->start();
}

void MainWindow::initComputerWidgets()
{
    qDebug() << "UI:" << "Initializing panel references.";
    ui->runControlsWidget->init(computer);
    ui->loaderWidget->init(computer);
    ui->disassemblyWidget->init(computer);
    ui->flagsWidget->init(computer);
    ui->memoryWidget->init(computer);
    ui->registersWidget->init(computer);
    ui->stackWidget->init(computer);
    ui->terminalWidget->init(computer);
    qDebug() << "UI:" << "Finished initializing panel info.";
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
    ui->loaderWidget->setEnabled(true);
}

void MainWindow::updateAllUI()
{
//    qDebug() << "UI:" << "Updating panel info:";
    ui->disassemblyWidget->updateDisassemblyText();
//    qDebug() << "UI:" << "Updated disassembly panel";
    ui->flagsWidget->updateFlags();
//    qDebug() << "UI:" << "Updated flags panel";
    ui->memoryWidget->updateMemoryDisplay();
//    qDebug() << "UI:" << "Updated memory panel";
    ui->registersWidget->updateRegisters();
//    qDebug() << "UI:" << "Updated registers panel";
    ui->stackWidget->updateStackDisplay();
//    qDebug() << "UI:" << "Updated registers panel";
    qDebug() << "UI:" << "Updated panel info.";
}
