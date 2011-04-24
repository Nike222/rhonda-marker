#include "stackedwidget.hpp"

StackedWidget::StackedWidget(QWidget *parent) :
    QStackedWidget(parent)
{
}


void StackedWidget::toProject()
{
	setCurrentIndex(SW_Project);
}

void StackedWidget::toObjects()
{
	setCurrentIndex(SW_Objects);
}

void StackedWidget::toFrames()
{
	setCurrentIndex(SW_Frames);
}

void StackedWidget::toMark()
{
	setCurrentIndex(SW_Mark);
}
