#include "abstractcontent.hpp"

#include <QDebug>
#include <QGraphicsScene>

AbstractContent::AbstractContent(QGraphicsScene *scene, QGraphicsItem *parent, bool noRescale, uint item_id)
	: SceneSelection(parent)
	, m_rotationAngle(0)
	, m_controlsVisible(false)
	, m_dirtyTransforming(false)
	, m_transformRefreshTimer(0)
	, m_rect(QRectF(-50, -50, 100, 100))
        , m_item_id(item_id)
        , m_shape_type(Rectangle)
{
	setAcceptHoverEvents(true);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemIsFocusable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	setAcceptedMouseButtons(Qt::LeftButton);

        /*
	createCorner(Qt::TopLeftCorner, noRescale);
	createCorner(Qt::TopRightCorner, noRescale);
	createCorner(Qt::BottomLeftCorner, noRescale);
	createCorner(Qt::BottomRightCorner, noRescale);
        */

        //layoutChildren();
}

AbstractContent::~AbstractContent()
{

}

void AbstractContent::dispose()
{
	SceneSelection::dispose();
}

QRectF AbstractContent::boundingRect() const
{
	return m_rect;
/*
	QRectF res = m_rect;
	res.setX(m_rect.x()-(m_rect.width()/2));
	res.setY(m_rect.y()-(m_rect.height()/2));
	return res;
*/
}

bool AbstractContent::is_hovered() const
{
	return m_controlsVisible;
}

void AbstractContent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	drawContent(painter, m_rect.toRect(), option);
}

void AbstractContent::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	setControlsVisible(true);
        bringToFront();
}

void AbstractContent::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	setControlsVisible(false);
        bringToBack();
}

/*
QString& AbstractContent::fullContentName()
{
    QString res(contentName() + " " + QString::number(m_item_id));
    return res;
}
*/

QVariant AbstractContent::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemPositionChange) {
		QPointF newPos = value.toPointF();
		QRectF rect = scene()->sceneRect();
		if (!rect.contains(newPos)) {
			newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
			newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
			return newPos;
		}
	}

	return value;
}

void AbstractContent::createCorner(uint corner, bool noRescale)
{
	CornerItem * c = new CornerItem(corner, this);
	c->setVisible(m_controlsVisible);
	c->setZValue(2.0);
	c->setToolTip(tr("Drag with Left or Right mouse button.\n - Hold down SHIFT for free resize\n - Hold down CTRL to rotate only\n - Hold down ALT to snap rotation\n - Double click (with LMB/RMB) to restore the aspect ratio/rotation"));
	m_cornerItems.append(c);
}

void AbstractContent::setControlsVisible(bool visible)
{
	m_controlsVisible = visible;
	foreach (CornerItem * corner, m_cornerItems)
		corner->setVisible(visible);
//    foreach (ButtonItem * button, m_controlItems)
//        button->setVisible(visible);
}

void AbstractContent::layoutChildren()
{
	// layout corners
	foreach (CornerItem *corner, m_cornerItems)
                corner->relayout(m_rect.toRect(), m_shape_type);
}

void AbstractContent::bringToFront()
{
        setZValue(10);
}

void AbstractContent::resizeContents(const QRect & rect, bool keepRatio)
{
	if (!rect.isValid())
		return;

	prepareGeometryChange();

	m_rect = rect;
/*
	if (keepRatio) {
		int hfw = contentHeightForWidth(rect.width());
		if (hfw > 1) {
			m_rect.setTop(-hfw / 2);
			m_rect.setHeight(hfw);
		}
	}
*/
	//m_frameRect = m_frame ? m_frame->frameRect(m_contentRect) : m_contentRect;

	layoutChildren();
	update();
}


void AbstractContent::delayedDirty(int ms)
{
	// tell rendering that we're changing stuff
	m_dirtyTransforming = true;

	// start refresh timer
	if (!m_transformRefreshTimer) {
		m_transformRefreshTimer = new QTimer(this);
		connect(m_transformRefreshTimer, SIGNAL(timeout()), this, SLOT(slotDirtyEnded()));
		m_transformRefreshTimer->setSingleShot(true);
	}
	m_transformRefreshTimer->start(ms);
}

void AbstractContent::slotDirtyEnded()
{
	m_dirtyTransforming = false;
	update();
}

void AbstractContent::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Backspace:
        dispose();
        break;

    case Qt::Key_Left:
        moveBy(-1, 0);
        break;

    case Qt::Key_Right:
        moveBy(1, 0);
        break;

    case Qt::Key_Up:
        moveBy(0, -1);
        break;

    case Qt::Key_Down:
        moveBy(0, 1);
        break;
    }
}

void AbstractContent::setPos(uint x, uint y)
{
    SceneSelection::setPos( x + (m_rect.width() / 2),
                            y + (m_rect.height() / 2));
}
