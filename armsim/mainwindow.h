/* mainwindow.cpp
 * Contains the MainWindow and is the hub for UI actions.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "options.h"
#include <QMainWindow>

// Qt magic "header" for the Widgets app.
namespace Ui {
class MainWindow;
}

// Main class to implement Qt Widgets.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Options &options, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Options &_options;
};

#endif // MAINWINDOW_H
