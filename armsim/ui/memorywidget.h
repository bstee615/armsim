#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>
#include "computerwidget.h"

namespace Ui {
class MemoryWidget;
}

class MemoryWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit MemoryWidget(QWidget *parent = nullptr);
    ~MemoryWidget();

    void updateMemoryDisplay();
    void updateMemoryDisplay(address startingAddress);
    void setStartingAddress(address startingAddress);

private slots:
    void on_btnEnterStartingAddress_clicked();

private:
    Ui::MemoryWidget *ui;
};

#endif // MEMORYWIDGET_H
