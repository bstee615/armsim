#ifndef FLAGSWIDGET_H
#define FLAGSWIDGET_H

#include <QWidget>

namespace Ui {
class FlagsWidget;
}

class FlagsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlagsWidget(QWidget *parent = nullptr);
    ~FlagsWidget();

private:
    Ui::FlagsWidget *ui;
};

#endif // FLAGSWIDGET_H
