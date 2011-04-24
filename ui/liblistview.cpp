#include "liblistview.h"
#include "QMessageBox"
#include <QSortFilterProxyModel>

LibListView::LibListView(QWidget *parent) :
    QListView(parent)
{
    lib.setSchema("/home/od1n/devel/qt/mproto/lib.xsd");
    lib.load("/home/od1n/devel/qt/mproto/lib.xml");
    model = new listModel ();
    this->setModel(model);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
}

void LibListView::on_right_clicked()
{
    int id = mothership->get_selection_id();
    LibraryGroup temp = lib.getGroupById(id);
    QList< QPair<QString, QString> >list = model->getList();
    QPair<QString, QString> pair(temp.name, QString("%1").arg(temp.id));
    if (!list.contains(pair)) {
        model->insertRows(0, 1, QModelIndex());
        QModelIndex index = model->index(0, 0, QModelIndex());
        model->setData(index, pair.first, Qt::EditRole);
        index = model->index(0, 1, QModelIndex());
        model->setData(index, pair.second, Qt::EditRole);
    } else {
        QMessageBox::information(this, tr("Duplicate Name"), tr("The name \"%1\" already exists.").arg(temp.name));
    }
    this->setModel(model);
}

void LibListView::on_left_clicked()
{
    //LibListView *temp = static_cast<LibListView*>(this);
    //QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = this->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QModelIndex index;

    foreach (index, indexes) {
        int row = index.row();
        model->removeRows(row, 1, QModelIndex());
    }
}
