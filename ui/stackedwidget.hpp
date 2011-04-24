#ifndef STACKEDWIDGET_HPP
#define STACKEDWIDGET_HPP

#include <QStackedWidget>

class StackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
	enum Pages {
		SW_Project	= 0,
		SW_Objects	= 1,
		SW_Frames	= 2,
		SW_Mark		= 3,
	};

    explicit StackedWidget(QWidget *parent = 0);

signals:


public slots:
	void toProject();
	void toObjects();
	void toFrames();
	void toMark();
};

#endif // STACKEDWIDGET_HPP
