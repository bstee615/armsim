/* mainwindow.cpp
 * Contains the MainWindow and is the hub for UI actions.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "options.h"
#include "computer.h"
#include "computerthreads.h"
#include "computerwidget.h"
#include <QMainWindow>

// Qt magic "header" for the Widgets app.
namespace Ui {
class MainWindow;
}

// Main class to implement Qt Widgets.
class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;
    Options &_options;

    ComputerThread *runningThread = nullptr;

    void setComputerThread(ComputerThread *computerThread);

public:
    // Initializes GUI elements with the specified Options.
    MainWindow(Options &options, QWidget *parent = nullptr);
    ~MainWindow();

    Computer *computer;

private slots:
    void startComputerRunThread();
    void startComputerStepThread();
    void stopComputerThread();
    void deleteComputerThread();

    void updateAllUI();
};

#endif // MAINWINDOW_H
