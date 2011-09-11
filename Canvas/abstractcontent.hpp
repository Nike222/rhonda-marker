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
#include <QPointF>

#include "sceneselection.hpp"
#include "corneritem.hpp"


class CornerItem;

class AbstractContent : public SceneSelection
{
    Q_OBJECT
public:
        AbstractContent(QGraphicsScene *scene, QGraphicsItem *parent = 0, bool noRescale = false, uint itemId = 0);
	~AbstractContent();

	void dispose();

        enum ShapeType {
            Rectangle = 0,
            Ellipse,
        };

        // size
//	QRect contentRect() const;
	void resizeContents(const QRect & rect, bool keepRatio = false);
//	void resetContentsRatio();
	void delayedDirty(int ms = 400);

	// to be reimplemented by subclasses
        virtual QString contentName() = 0;
	virtual void drawContent(QPainter *painter, const QRect &targetRect, const QStyleOptionGraphicsItem *option) = 0;

//        QString& fullContentName();
        uint itemId() { return m_item_id; }
        void setId(uint id) { m_item_id = id; }
        void setShape(uint shape) { m_shape_type = shape; }

	QRectF boundingRect() const;
	virtual QPainterPath shape() const = 0;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
	bool is_hovered() const;

        void setPos(uint x, uint y);

signals:

public slots:
        void bringToFront();
        void bringToBack() { setZValue(0); }

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	void setControlsVisible(bool visible);
//	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
        void createCorner(uint corner, bool noRescale);
        void layoutChildren();

private slots:
	void slotDirtyEnded();

private:

	double m_rotationAngle;
	bool m_controlsVisible;
	bool m_dirtyTransforming;
	QTimer *m_transformRefreshTimer;

	QRectF m_rect;
	QList<CornerItem *> m_cornerItems;

        uint m_item_id;
        uint m_shape_type;
};

#endif // ABSTRACTCONTENT_HPP
