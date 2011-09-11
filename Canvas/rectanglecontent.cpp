#include "rectanglecontent.hpp"

#include <QColor>
#include <QPen>
#include <QBrush>

RectangleContent::RectangleContent(QGraphicsScene *scene, QGraphicsItem *parent, bool noRescale)
	: AbstractContent(scene, parent, noRescale)
{
    setShape(AbstractContent::Rectangle);

    createCorner(TopLeft, noRescale);
    createCorner(TopRight, noRescale);
    createCorner(BottomLeft, noRescale);
    createCorner(BottomRight, noRescale);

    createCorner(Top, noRescale);

    layoutChildren();
}

RectangleContent::~RectangleContent()
{

}

QPainterPath RectangleContent::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

QString RectangleContent::contentName()
{
    return QString("Rectangle ") + QString::number(itemId());
}

void RectangleContent::drawContent(QPainter *painter, const QRect &targetRect, const QStyleOptionGraphicsItem *option)
{
	QColor color(16, 200, 29);
	painter->setPen(QPen(color));
	painter->drawRect(targetRect);

	if (is_hovered()) {
		color.setAlpha(50);
		painter->fillRect(targetRect, QBrush(color));
		update();
	}
}

