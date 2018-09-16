#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options &options, QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::MainWindow),
    _options(options),
    computer(Computer(_options.getMemory(), _options.getFilename()))
{
    ui->setupUi(this);
    ui->loaderWidget->init(&computer);
    ui->loaderWidget->setFileDialogText(_options.getFilename());

    ui->runControlsWidget->init(&computer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
