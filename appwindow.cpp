#include "appwindow.h"
#include "ui_appwindow.h"

#include <QFileDialog>
#include <QDebug>

#include "Canvas/canvasview.hpp"

AppWindow::AppWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppWindow)
{
    ui->setupUi(this);
    //QObject::connect(ui->buttonLoadImage, SIGNAL(clicked()), this, SLOT(on_buttonLoadImage_clicked()));
}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::on_buttonLoadImage_clicked()
{
    QString imageFile = QFileDialog::getOpenFileName (
            this,
            tr("Open Image..."),
            "/home",
            tr("Images (*.png *.jpg)"));
    if (!imageFile.isEmpty ()) {
        qDebug() << imageFile;
		QPixmap pix;
		if (pix.load(imageFile)) {
			ui->graphicsView->SetPicture (pix);
			QSize s = pix.size ();
			// ui->graphicsView->setSceneRect (0, 0, s.width(), s.height());
			// ui->graphicsView->show();
		} else {

		}
    }


}
