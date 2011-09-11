#ifndef CANVASSCENE_HPP
#define CANVASSCENE_HPP

#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QPainter>

class CanvasScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit CanvasScene(QObject *parent = 0);
	void setPixmap(QPixmap pix);
	void setScaling(qreal scale);

signals:
	void mouseMoved(QPointF);

public slots:

protected:
	enum State {
		sDefault,
		sAddItem,
	};

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void drawBackground(QPainter *painter, const QRectF &rect);

private:
	QPixmap m_pix;
	qreal m_scale;
};

#endif // CANVASSCENE_HPP
