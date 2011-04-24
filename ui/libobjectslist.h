#ifndef LIBOBJECTSLIST_H
#define LIBOBJECTSLIST_H

#include <QTreeView>
#include "libs/TreeModel/xmlModel.h"

class LibObjectsList : public QTreeView
{
    Q_OBJECT
    xmlModel *model;
    XmlLibrary lib;
public:
    explicit LibObjectsList(QWidget *parent = 0);
    quint32 get_selection_id();
signals:

public slots:

};

#endif // LIBOBJECTSLIST_H
