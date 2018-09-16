#include "computerwidget.h"

void ComputerWidget::init(Computer *computer)
{
    _computer = computer;
    _computer->registerObserver(this);
}
