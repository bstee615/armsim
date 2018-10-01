#ifndef ADDBREAKPOINTPOPUP_H
#define ADDBREAKPOINTPOPUP_H

#include <QDialog>
#include "computerwidget.h"

namespace Ui {
class AddBreakpointPopup;
}

class AddBreakpointPopup : public QDialog, public ComputerWidget
{
    Q_OBJECT

public:
    explicit AddBreakpointPopup(QWidget *parent = nullptr);
    ~AddBreakpointPopup();

    int lastValue;

signals:
    void addedBreakpoint();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddBreakpointPopup *ui;
};

#endif // ADDBREAKPOINTPOPUP_H
