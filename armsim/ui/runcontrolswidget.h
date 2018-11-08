#ifndef RUNCONTROLSWIDGET_H
#define RUNCONTROLSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "computerthreads.h"
#include "computerwidget.h"
#include "addbreakpointpopup.h"

namespace Ui {
class RunControlsWidget;
}

class RunControlsWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit RunControlsWidget(QWidget *parent = nullptr);
    ~RunControlsWidget();

    void update() {}
    QPushButton *btnRun;
    QPushButton *btnStep;
    QPushButton *btnStop;
    AddBreakpointPopup *popup;

    void init(Computer *computer);
    void startTrace();

public slots:
    void setRunningState(bool running);

private slots:
    void on_btnRun_clicked();

    void on_btnStep_clicked();

    void on_btnStop_clicked();

    void on_btnAddBreakpoint_clicked();

    void onAddedBreakpoint();

    void toggleTrace();

    void on_checkTrace_toggled(bool checked);

signals:
    void toggledBreakpoint();

private:
    Ui::RunControlsWidget *ui;
};

#endif // RUNCONTROLSWIDGET_H
