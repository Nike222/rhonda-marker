#include <QtGui/QApplication>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("moais_1");
	QCoreApplication::setOrganizationDomain("moais.ru");
	QCoreApplication::setApplicationName("Marker");

	QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
