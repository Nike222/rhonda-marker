#ifndef ABSTRACTCONTENT_HPP
#define ABSTRACTCONTENT_HPP

#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QList>
#include <QFocusEvent>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QVariant>
#include <QTimer>
#include <QKeyEvent>

#include "sceneselection.hpp"
#include "corneritem.hpp"

class CornerItem;

class AbstractContent : public SceneSelection
{
    Q_OBJECT
public:
	AbstractContent(QGraphicsScene *scene, QGraphicsItem *parent = 0, bool noRescale = false);
	~AbstractContent();

	void dispose();

	// size
//	QRect contentRect() const;
	void resizeContents(const QRect & rect, bool keepRatio = false);
//	void resetContentsRatio();
	void delayedDirty(int ms = 400);

	// to be reimplemented by subclasses
	virtual QString contentName() const = 0;
	virtual void drawContent(QPainter *painter, const QRect &targetRect, const QStyleOptionGraphicsItem *option) = 0;

	QRectF boundingRect() const;
	virtual QPainterPath shape() const = 0;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
	bool is_hovered() const;

signals:

public slots:

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	void setControlsVisible(bool visible);
//	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

private slots:
	void slotDirtyEnded();

private:
	void createCorner(Qt::Corner, bool noRescale);
	void layoutChildren();

	double m_rotationAngle;
	bool m_controlsVisible;
	bool m_dirtyTransforming;
	QTimer *m_transformRefreshTimer;

	QRectF m_rect;
	QList<CornerItem *> m_cornerItems;
};

#endif // ABSTRACTCONTENT_HPP
