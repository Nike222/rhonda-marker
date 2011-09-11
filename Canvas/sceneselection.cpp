#include "sceneselection.hpp"

SceneSelection::SceneSelection(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
	show();
}

void SceneSelection::dispose()
{
	deleteLater();
}
