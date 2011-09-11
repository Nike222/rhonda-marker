#ifndef RECTANGLECONTENT_HPP
#define RECTANGLECONTENT_HPP

#include <QPainterPath>

#include "abstractcontent.hpp"

class RectangleContent : public AbstractContent
{
    Q_OBJECT
public:
	RectangleContent(QGraphicsScene *scene, QGraphicsItem *parent = 0, bool noRescale = false);
	~RectangleContent();

	QPainterPath shape() const;

	QString contentName() const;
	void drawContent(QPainter *painter, const QRect &targetRect, const QStyleOptionGraphicsItem *option);

signals:

public slots:

};

#endif // RECTANGLECONTENT_HPP
