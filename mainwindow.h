#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "options.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Options &options, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Options &_options;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
