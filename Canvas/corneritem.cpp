#include "corneritem.hpp"

#include <math.h>
#include <QDebug>

CornerItem::CornerItem(uint corner, AbstractContent * parent)
	: QGraphicsItem(parent)
	, m_content(parent)
	, m_corner(corner)
	, m_opMask(/*rotateOnly ? Rotate | FixRotate :*/ AllowAll)
	, m_side(8)
	, m_operation(Off)
{
	setAcceptsHoverEvents(true);
}

void CornerItem::relayout(const QRect & rect, uint shape)
{
	// change side, if needed
	int side = 1 + (int)sqrt((float)qMin(rect.width(), rect.height()));
	if (side != m_side) {
		prepareGeometryChange();
		m_side = side;
	}

        switch (m_corner) {
                case TopLeft:       setPos(rect.topLeft() + QPoint(m_side, m_side)); break;
                case TopRight:      setPos(rect.topRight() + QPoint(-m_side + 1, m_side)); break;
                case BottomLeft:    setPos(rect.bottomLeft() + QPoint(m_side, -m_side + 1)); break;
                case BottomRight:   setPos(rect.bottomRight() + QPoint(-m_side + 1, -m_side + 1)); break;

                case Left:          setPos(QPoint(rect.topLeft().x(), 0) + QPoint(m_side, 0)); break;
                case Right:         setPos(QPoint(rect.topRight().x()+1, 0) + QPoint(-m_side, 0)); break;
                case Top:           setPos(QPoint(0, rect.topLeft().y()) + QPoint(0, m_side)); break;
                case Bottom:        setPos(QPoint(0, rect.bottomLeft().y()) + QPoint(0, -m_side)); break;
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
        m_startSize = QPointF(cRect.width(), cRect.height());

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

        QPointF v = pos() + event->pos();
#if 0
	// vector relative to the centre
        switch ( m_corner ) {
            case Left:
            case Right:
            {
                v.setX(v.x() + event->pos().x());
                v.setY(0);
                break;
            }

            case Top:
            case Bottom:
            {
                v.setY(v.y() + event->pos().y());
                v.setX(0);
                break;
            }

            case TopLeft:
            case BottomLeft:
            case BottomRight:
            case TopRight:
            default:
            {
                v.setY(v.y() + event->pos().y());
                v.setX(v.x() + event->pos().x());
                break;
            }
        }
#endif
        qDebug() << pos() << " " << event->pos() << " " << v;
	if (v.isNull())
		return;

	// do scaling
	m_content->delayedDirty();
	if (op & Scale) {
                int W, H;
		if (op & FixScale) {
                        const double r = m_startRatio;
                        const double D = sqrt(v.x()*v.x() + v.y()*v.y()); // vector length
                        double K = 1;
                        switch (m_corner) {
                        case TopLeft:
                        case TopRight:
                        case BottomLeft:
                        case BottomRight:
                        {
                            K = sqrt(1 + 1/(r * r));
                            break;
                        }
                        case Left:
                        case Right:
                        case Top:
                        case Bottom:
                        default:
                        {
                            K = 1;
                            break;
                        }
                        }

                        // const double K = sqrt(1 + 1/(r * r));

                        W = qMax((int)((2*D)/(K)), 40);
                        H = qMax((int)((2*D)/(r*K)), 40);
                        //m_content->resizeContents(QRect(-W / 2, -H / 2, W, H));
		} else {
                    double mH, mW;
                    switch (m_corner) {
                    case Left:
                    case Right:
                        mW = 40.0;
                        mH = qMax(40.0, m_startSize.y());
                        break;
                    case Top:
                    case Bottom:
                        mW = qMax(40.0, m_startSize.x());
                        mH = 40.0;
                        break;
                    default:
                    {
                        mW = qMax(40.0, m_startSize.x());
                        mH = qMax(40.0, m_startSize.y());
                        break;
                    }

                    }

                    W = qMax(2 * fabs(v.x()), mW); //(m_contentRect.width() * v.x()) / oldPos.x();
                        H = qMax(2 * fabs(v.y()), mH); //(m_contentRect.height() * v.y()) / oldPos.y();
			//if (W != (int)cRect.width() || H != (int)cRect.height())
                       //         m_content->resizeContents(QRect(-W / 2, -H / 2, W, H));
		}
                m_content->resizeContents(QRect(-W / 2, -H / 2, W, H));
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
