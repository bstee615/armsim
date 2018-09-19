#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options &options, QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::MainWindow),
    _options(options),
    computer(new Computer(_options.getMemory()))
{
    ui->setupUi(this);
    initComputerWidgets();

    ui->runControlsWidget->setRunningState(false);

    connect(ui->runControlsWidget->btnRun, SIGNAL(clicked(bool)), this, SLOT(startComputerRunThread()));
    connect(ui->runControlsWidget->btnStep, SIGNAL(clicked(bool)), this, SLOT(startComputerStepThread()));
    connect(ui->runControlsWidget->btnStop, SIGNAL(clicked(bool)), this, SLOT(stopComputerThread()));
    connect(ui->runControlsWidget, SIGNAL(addedBreakpoint()), this, SLOT(updateAllUI()));
    connect(ui->loaderWidget, SIGNAL(loadedFile()), this, SLOT(updateAllUI()));

    computer->cpu.setGeneralRegister(13, 0x1054);
    ui->loaderWidget->loadFile(_options.getFilename());
    ui->memoryWidget->setStartingAddress(computer->cpu.getProgramCounter());
}

MainWindow::~MainWindow()
{
//    computer->stopTrace();
    delete computer;
    delete ui;
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
    qDebug() << "UI:" << "Updating panel info.";
    ui->disassemblyWidget->updateDisassemblyText();
    ui->flagsWidget->updateFlags();
    ui->memoryWidget->updateMemoryDisplay();
    ui->registersWidget->updateRegisters();
    ui->stackWidget->updateStackDisplay();
}
