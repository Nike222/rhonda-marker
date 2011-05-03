#ifndef RECENTDOCS_H
#define RECENTDOCS_H

#include <QAbstractListModel>
#include <QList>
#include <QStringList>

#define MAX_RECENT_COUNT 10

class RecentDocs : public QAbstractListModel
{
    Q_OBJECT

public:
    RecentDocs(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

signals:
    void dataChanged();

public slots:
    void addFilename(QString filename);

private:
    QStringList m_filenames;
    int m_filecount;
};

#endif // RECENTDOCS_H
