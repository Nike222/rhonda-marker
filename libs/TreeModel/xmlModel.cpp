#include "xmlModel.h"

xmlModel::xmlModel(XmlLibrary &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "ID" << "Groups";
    rootItem = new xmlItem(rootData);
    setupModelData(data, rootItem);
}

xmlModel::~xmlModel()
{
    delete rootItem;
}

int xmlModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<xmlItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant xmlModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    xmlItem *item = static_cast<xmlItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags xmlModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant xmlModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex xmlModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    xmlItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<xmlItem*>(parent.internalPointer());

    xmlItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex xmlModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    xmlItem *childItem = static_cast<xmlItem*>(index.internalPointer());
    xmlItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int xmlModel::rowCount(const QModelIndex &parent) const
{
    xmlItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<xmlItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void xmlModel::setupModelData(XmlLibrary &lib, xmlItem *parent)
{
    QList<xmlItem*> parents;
    QList<uint> level;
    parents << parent;
    level << 0;
    int number = 0;
    int count = lib.groupCount();
    while (number < count) {
        QList<QVariant> columnData;
        LibraryGroup group = lib.getGroupByNo(number);
        columnData << group.id << group.name;
        if (group.parentId > level.last()) {
            if (parents.last()->childCount() > 0) {
                parents << parents.last()->child(parents.last()->childCount()-1);
                level << group.parentId;
            }
        } else {
            while (group.parentId < level.last() && parents.count() > 0) {
                    parents.pop_back();
                    level.pop_back();
            }
        }
        parents.last()->appendChild(new xmlItem(columnData, parents.last()));
        number++;
    }
}

uint xmlModel::addGroup(XmlLibrary &lib, uint id, QString name, uint parent){
    QList<xmlItem*> parents;
    QList<uint> level;
    parents << rootItem;
    LibraryGroup s = lib.getGroupById(id);
    level << s.parentId;
    while (level.last() != 0) {
        LibraryGroup temp = lib.getGroupById(level.last());
        level << temp.parentId;
    }
    level.pop_back();
    while (parents.last()->data(0).toUInt() != parent){
        int count = parents.last()->childCount();
        for (int i = 0; i < count; i++){
            if (parents.last()->child(i)->data(0).toUInt() == level.last()) {
                parents << parents.last()->child(i);
                level.pop_back();
                break;
            }
        }
    }
    QList<QVariant> columnData;
    columnData << id << name;
    parents.last()->appendChild(new xmlItem(columnData,parents.last()));
    return 0;
}
