#ifndef SCENESELECTION_HPP
#define SCENESELECTION_HPP

#include <QGraphicsObject>

class SceneSelection : public QGraphicsObject
{
    Q_OBJECT
public:
	SceneSelection(QGraphicsItem *parent = 0);

	virtual void dispose();
signals:

public slots:

};

#endif // SCENESELECTION_HPP
