#ifndef RUNCONTROLSWIDGET_H
#define RUNCONTROLSWIDGET_H

#include <QWidget>
#include <QThread>
#include "computerwidget.h"

namespace Ui {
class RunControlsWidget;
}

class RunControlsWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit RunControlsWidget(QWidget *parent = nullptr);
    ~RunControlsWidget();

    void update();

private slots:
    void on_btnRun_clicked();

    void on_btnStep_clicked();
    void updateUIToRunningState();

private:
    Ui::RunControlsWidget *ui;
    QThread *runningThread = nullptr;
    bool isRunning;
    void setRunningState(bool running);
};

#endif // RUNCONTROLSWIDGET_H
