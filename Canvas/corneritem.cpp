#include "corneritem.hpp"

#include <math.h>
#include <QDebug>

CornerItem::CornerItem(Qt::Corner corner, AbstractContent * parent)
	: QGraphicsItem(parent)
	, m_content(parent)
	, m_corner(corner)
	, m_opMask(/*rotateOnly ? Rotate | FixRotate :*/ AllowAll)
	, m_side(8)
	, m_operation(Off)
{
	setAcceptsHoverEvents(true);
}

void CornerItem::relayout(const QRect & rect)
{
	// change side, if needed
	int side = 1 + (int)sqrt((float)qMin(rect.width(), rect.height()));
	if (side != m_side) {
		prepareGeometryChange();
		m_side = side;
	}

	// place at the right corner
	switch (m_corner) {
		case Qt::TopLeftCorner: setPos(rect.topLeft() + QPoint(m_side, m_side)); break;
		case Qt::TopRightCorner: setPos(rect.topRight() + QPoint(-m_side + 1, m_side)); break;
		case Qt::BottomLeftCorner: setPos(rect.bottomLeft() + QPoint(m_side, -m_side + 1)); break;
		case Qt::BottomRightCorner: setPos(rect.bottomRight() + QPoint(-m_side + 1, -m_side + 1)); break;
	}
}

QRectF CornerItem::boundingRect() const
{
	return QRectF(-m_side, -m_side, 2*m_side, 2*m_side);
}

void CornerItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * /*widget*/)
{
	QColor color(222, 241, 16);
	if (option->state & QStyle::State_MouseOver) {
		if (m_operation != Off)
			color.setAlpha(250);
		else
			color.setAlpha(196);
	} else
		color.setAlpha(128);
	painter->fillRect(boundingRect(), color);
}

void CornerItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	event->accept();

	// do the right op
	switch (event->button()) {
		case Qt::LeftButton:    m_operation = Rotate | Scale | FixScale; break;
		case Qt::RightButton:   m_operation = Scale | FixScale; break;
		case Qt::MidButton:     m_operation = Scale; break;
		default:                m_operation = Off; return;
	}

	// filter out unwanted operations
	m_operation &= m_opMask;

	// intial parameters
	QRectF cRect = m_content->boundingRect();
	m_startRatio = cRect.width() / cRect.height();

	update();
}

void CornerItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	if (m_operation == Off)
		return;
	event->accept();

	// modify the operation using the shortcuts
	int op = m_operation;
	if (event->modifiers() & Qt::ShiftModifier)
		op &= ~FixScale & ~Rotate;
	if (event->modifiers() & Qt::ControlModifier)
		//op |= FixRotate;
		op |= Rotate;
	if (event->modifiers() & Qt::AltModifier)
		//op &= ~(Scale | FixScale);
		op |= FixRotate;
	op &= m_opMask;
	if ((op & (Rotate | Scale)) == (Rotate | Scale))
		op |= FixScale;
	if ((op & (Rotate | Scale)) == Off)
		return;

	// vector relative to the centre
	QPointF v = pos() + event->pos();
	if (v.isNull())
		return;

	// do scaling
	m_content->delayedDirty();
	if (op & Scale) {
		if (op & FixScale) {
			const double r = m_startRatio;
			const double D = sqrt(v.x()*v.x() + v.y()*v.y());
			const double K = sqrt(1 + 1/(r * r));
			int W = qMax((int)((2*D)/(K)), 50);
			int H = qMax((int)((2*D)/(r*K)), 40);
			m_content->resizeContents(QRect(-W / 2, -H / 2, W, H));
		} else {
			int W = qMax(2 * fabs(v.x()), 50.0); //(m_contentRect.width() * v.x()) / oldPos.x();
			int H = qMax(2 * fabs(v.y()), 40.0); //(m_contentRect.height() * v.y()) / oldPos.y();
			//if (W != (int)cRect.width() || H != (int)cRect.height())
				m_content->resizeContents(QRect(-W / 2, -H / 2, W, H));
		}
	}

	// do rotation
	if (op & Rotate) {
		QPointF refPos = pos();

		// set item rotation (set rotation relative to current)
		qreal refAngle = atan2(refPos.y(), refPos.x());
		qreal newAngle = atan2(v.y(), v.x());
		double dZr = 57.29577951308232 * (newAngle - refAngle); // 180 * a / M_PI
		double zr = m_content->rotation() + dZr;

		// snap to M_PI/4
		if (op & FixRotate) {
			int fracts = (int)((zr - 7.5) / 15.0);
			zr = (qreal)fracts * 15.0;
		}

		// apply rotation
		m_content->setRotation(zr);
	}
}

void CornerItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	event->accept();
	bool accepted = m_operation != Off;
	m_operation = Off;
	update();

	// clicked
	if (accepted) {
	}
}
