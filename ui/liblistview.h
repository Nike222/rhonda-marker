#ifndef LIBLISTVIEW_H
#define LIBLISTVIEW_H

#include <QListView>
#include "libobjectslist.h"
#include "../libs/ListModel/listModel.h"
#include "../libs/xmllib/xmllibrary.hpp"

class LibListView : public QListView
{
    Q_OBJECT
    LibObjectsList *mothership;
    listModel *model;
    XmlLibrary lib;
public:
    explicit LibListView(QWidget *parent = 0);
    void setMother(LibObjectsList *mother){mothership = mother;}

signals:

public slots:
    void on_right_clicked();
    void on_left_clicked();
};

#endif // LIBLISTVIEW_H
