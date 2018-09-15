#ifndef DISASSEMBLYWIDGET_H
#define DISASSEMBLYWIDGET_H

#include <QWidget>

namespace Ui {
class DisassemblyWidget;
}

class DisassemblyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisassemblyWidget(QWidget *parent = nullptr);
    ~DisassemblyWidget();

private:
    Ui::DisassemblyWidget *ui;
};

#endif // DISASSEMBLYWIDGET_H
