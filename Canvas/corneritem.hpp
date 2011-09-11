#ifndef CORNERITEM_HPP
#define CORNERITEM_HPP

#include <QGraphicsItem>
#include "abstractcontent.hpp"

class AbstractContent;

enum Corner {
    TopLeft = 0,
    Top,
    TopRight,
    Right,
    BottomRight,
    Bottom,
    BottomLeft,
    Left
};

class CornerItem : public QGraphicsItem
{
public:
        CornerItem(uint corner, AbstractContent *parent);
	~CornerItem() {}

        void relayout(const QRect & rect, uint shape);

	QRectF boundingRect() const;
//	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

private:
	enum Operation {
		Off         = 0x0000,
		Rotate      = 0x0001,
		FixRotate   = 0x0002,
		Scale       = 0x0010,
		FixScale    = 0x0020,
		AllowAll    = 0xFFFF,
	};

	AbstractContent *m_content;
        uint m_corner;
	int m_opMask;
	int m_side;
	int m_operation;
	double m_startRatio;
        QPointF m_startSize;
};

#endif // CORNERITEM_HPP
