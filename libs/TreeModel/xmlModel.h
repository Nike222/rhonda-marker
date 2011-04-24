#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "xmlItem.h"
#include "../xmllib/xmllibrary.hpp"

class xmlItem;

class xmlModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    xmlModel(XmlLibrary &data, QObject *parent = 0);
    ~xmlModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    uint addGroup(XmlLibrary &lib, uint id, QString name, uint parent);

private:
    void setupModelData(XmlLibrary &lib, xmlItem *parent);
    xmlItem *rootItem;
};

#endif
