#ifndef CANVASVIEW_HPP
#define CANVASVIEW_HPP

#include <QGraphicsView>
#include <QList>
#include <QRect>
#include <QPixmap>
#include <QContextMenuEvent>

#include "canvasscene.hpp"

class CanvasView : public QGraphicsView
{
    Q_OBJECT
	Q_PROPERTY(qreal viewScale READ viewScale WRITE setViewScale NOTIFY viewScaleChanged)
public:
	CanvasView(QWidget * parent = 0);
	~CanvasView();

	void SetPicture (QPixmap &pix);
	void SetObjects (QList<QRect> &obqList);
	void SetObjectProperties (quint16 objId, QRect $props);

	qreal viewScale();
	void setViewScale(qreal scale);

protected:
	void resizeEvent(QResizeEvent *event);
	void contextMenuEvent(QContextMenuEvent *event);

signals:
	void ObjectChanged();
	void ObjectSelected();
	void viewScaleChanged();

public slots:
	// void ChangeObject(quint16 objId, QRect &props);

private:
	qreal m_viewScale;
	CanvasScene *scene;

	void layoutScene();

	QList<QGraphicsItem *> m_itemsList;

private slots:
	void createDot();
	void createRect();
	void createEllipse();

};

#endif // CANVASVIEW_HPP
