#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options &options, QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::MainWindow),
    _options(options)
{
    ui->setupUi(this);

    ui->loaderWidget->initializeRAM(_options.getMemory());
    ui->loaderWidget->loadFile(_options.getFilename());
}

MainWindow::~MainWindow()
{
    delete ui;
}
