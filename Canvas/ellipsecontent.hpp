#ifndef ELLIPSECONTENT_HPP
#define ELLIPSECONTENT_HPP

#include "abstractcontent.hpp"

class EllipseContent : public AbstractContent
{
	Q_OBJECT
public:
	EllipseContent(QGraphicsScene *scene, QGraphicsItem *parent = 0, bool noRescale = false);
	~EllipseContent();

	QPainterPath shape() const;

	QString contentName() const;
	void drawContent(QPainter *painter, const QRect &targetRect, const QStyleOptionGraphicsItem *option);

signals:

public slots:

};

#endif // ELLIPSECONTENT_HPP
