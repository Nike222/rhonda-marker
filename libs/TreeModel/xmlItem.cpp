#include "xmlItem.h"

xmlItem::xmlItem(const QList<QVariant> &data, xmlItem *parent)
{
    parentItem = parent;
    itemData = data;
}

xmlItem::~xmlItem()
{
    qDeleteAll(childItems);
}

void xmlItem::appendChild(xmlItem *item)
{
    childItems.append(item);
}

xmlItem *xmlItem::child(int row)
{
    return childItems.value(row);
}

int xmlItem::childCount() const
{
    return childItems.count();
}

int xmlItem::columnCount() const
{
    return itemData.count();
}

QVariant xmlItem::data(int column) const
{
    return itemData.value(column);
}

xmlItem *xmlItem::parent()
{
    return parentItem;
}

int xmlItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<xmlItem*>(this));

    return 0;
}
