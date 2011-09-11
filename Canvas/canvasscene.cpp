#include "canvasscene.hpp"

#include <QDebug>

CanvasScene::CanvasScene(QObject *parent)
	: QGraphicsScene(parent)
	, m_scale(1)
{
	setStickyFocus(false);
}

void CanvasScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	emit mouseMoved(event->scenePos());
	QGraphicsScene::mouseMoveEvent(event);
}

void CanvasScene::setPixmap(QPixmap pix)
{
	m_pix = pix;
}

void CanvasScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	painter->drawPixmap(0, 0, m_pix);
}

void CanvasScene::setScaling(qreal scale)
{
	m_scale = scale;
}
