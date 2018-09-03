#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options &options, QWidget *parent):
    QMainWindow (parent),
    _options(options),
    ui(new Ui::MainWindow)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
