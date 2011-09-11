#include "ellipsecontent.hpp"

#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainterPath>

EllipseContent::EllipseContent(QGraphicsScene *scene, QGraphicsItem *parent, bool noRescale)
	: AbstractContent(scene, parent, noRescale)
{
}

EllipseContent::~EllipseContent()
{

}

QPainterPath EllipseContent::shape() const
{
	QPainterPath path;
	path.addEllipse(boundingRect());
	return path;
}

QString EllipseContent::contentName() const
{
	return QString("Ellipse");
}

void EllipseContent::drawContent(QPainter *painter, const QRect &targetRect, const QStyleOptionGraphicsItem *option)
{
	QColor color(16, 200, 29);
	painter->setPen(QPen(color));
	painter->drawEllipse(targetRect);

	if (is_hovered()) {
		color.setAlpha(50);
		QPainterPath path;
		path.addEllipse(targetRect);
		painter->fillPath(path, QBrush(color));
		update();
	}
}
