#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QStringList>

class xmlItem
{
public:
    xmlItem(const QList<QVariant> &data, xmlItem *parent = 0);
    ~xmlItem();
    void appendChild(xmlItem *child);
    xmlItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    xmlItem *parent();
private:
    QList<xmlItem*> childItems;
    QList<QVariant> itemData;
    xmlItem *parentItem;
};

#endif
