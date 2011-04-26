#include "libobjectslist.h"

LibObjectsList::LibObjectsList(QWidget *parent) :
    QTreeView(parent)
{
    lib.setSchema("/home/od1n/devel/qt/sources/marker/SampleFiles/lib.xsd");
    lib.load("/home/od1n/devel/qt/sources/marker/SampleFiles/lib.xml");
    model = new xmlModel (lib);
    this->setModel(model);
}

quint32 LibObjectsList::get_selection_id()
{
   return model->data(model->index((this->selectionModel()->currentIndex()).row(),0),0).toUInt();
}
