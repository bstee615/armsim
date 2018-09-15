#ifndef DISASSEMBLYWIDGET_H
#define DISASSEMBLYWIDGET_H

#include <QWidget>
#include "computerwidget.h"

namespace Ui {
class DisassemblyWidget;
}

class DisassemblyWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit DisassemblyWidget(QWidget *parent = nullptr);
    ~DisassemblyWidget();

private:
    Ui::DisassemblyWidget *ui;
};

#endif // DISASSEMBLYWIDGET_H
