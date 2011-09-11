#include "canvasview.hpp"

#include <QImage>
#include <QDebug>
#include <QMenu>
#include <QGraphicsRectItem>
#include <QGraphicsItem>

#include "ellipsecontent.hpp"
#include "rectanglecontent.hpp"

CanvasView::CanvasView(QWidget *parent) :
    QGraphicsView(parent)
    , items_counter(0)
{
	scene = 0;
}

CanvasView::~CanvasView ()
{
	if (scene != 0) {
		delete scene;
	}
}

void CanvasView::SetPicture (QPixmap &pix)
{
	/* if (scene() != 0) {

	} */
	if (scene != 0) {
		delete scene;
	}

	scene = new CanvasScene;
	scene->setSceneRect(pix.rect());
//	scene->setBackgroundBrush(pix);
	scene->setPixmap(pix);
//	scene->addPixmap (pix);
	setScene (scene);
	layoutScene();
}

qreal CanvasView::viewScale ()
{
	return m_viewScale;
}

void CanvasView::setViewScale (qreal scale)
{
	if (scale != m_viewScale) {
		m_viewScale = scale;
		if ((scale >= 0.98) && (scale <= 1.02))	{
			scale = 1;
			setTransform(QTransform());
		} else {
			QTransform t;
			t.scale (scale, scale);
			setTransform(t);
		}
		scene->setScaling(scale);
		emit viewScaleChanged();
	}
}

void CanvasView::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	layoutScene();
}

void CanvasView::layoutScene()
{
	if (scene != 0) {
		QRectF s = scene->sceneRect();
		QRect v = contentsRect();
		qreal scale_h = v.height() / s.height();
		qreal scale_w = v.width() / s.width();

		qreal scale = (scale_h < scale_w) ? scale_h : scale_w;
		if (scale > 1)
			scale = 1;
		setViewScale(scale);
	}
}

void CanvasView::createDot()
{
	qDebug() << "want create DOT";
}

void CanvasView::createRect()
{
	qDebug() << "want create RECT";

	RectangleContent *rect = new RectangleContent(scene);
	scene->addItem(static_cast<QGraphicsItem *>(rect));
        rect->setId(++items_counter);

        QPointF lpos(mapToScene(m_menuPos));
        rect->setPos(lpos.x(), lpos.y());
}

void CanvasView::createEllipse()
{
	qDebug() << "want create ELLIPSE";

	EllipseContent *item = new EllipseContent(scene);
	scene->addItem(static_cast<QGraphicsItem *>(item));
        item->setId(++items_counter);

        QPointF lpos(mapToScene(m_menuPos));
        item->setPos(lpos.x(), lpos.y());
}

void CanvasView::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);

	QAction *act;

        m_menuPos = QPoint(event->x(), event->y());

	m_itemsList = scene->items(mapToScene(event->pos()));
	qDebug() << "m_itemsList.length: " << m_itemsList.length();

	if (m_itemsList.length() > 0) {
		menu.addAction("Select Item:");
		foreach (QGraphicsItem *item, m_itemsList) {
			AbstractContent *i = dynamic_cast<AbstractContent *>(item);
                        if (i) {
				act = menu.addAction(i->contentName());
                                connect(act, SIGNAL(triggered()), i, SLOT(bringToFront()));
                        }
		}
	} else {
		menu.addAction("No items");
	}

	menu.addSeparator();
	menu.addAction("Add Item:");

	act = menu.addAction("Add Rectangle");
	connect(act, SIGNAL(triggered()), this, SLOT(createRect()));

	act = menu.addAction("Add Ellipse");
	connect(act, SIGNAL(triggered()), this, SLOT(createEllipse()));

	menu.exec(this->mapToGlobal(event->pos()));
}
