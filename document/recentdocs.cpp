#include "recentdocs.h"

#include "QDebug"
#include <QSettings>
#include <QApplication>
#include <QPalette>
#include <QBrush>
#include <QDir>

RecentDocs::RecentDocs(QObject *parent)
        : QAbstractListModel(parent)
{
    QSettings settings;

    settings.beginGroup("RecentDocs");
    m_filenames = settings.value("recentdocs", QStringList()).toStringList();
    settings.endGroup();

    if (m_filenames.count() > MAX_RECENT_COUNT)
        m_filenames.erase(m_filenames.begin()+MAX_RECENT_COUNT, m_filenames.end());

    m_filecount = m_filenames.count();
}

void RecentDocs::addFilename(QString filename)
{
    if (m_filenames.contains(filename)){
        m_filenames.move(m_filenames.indexOf(filename), 0);
    } else {
        m_filenames.prepend(filename);
        m_filecount++;
        if (m_filecount > MAX_RECENT_COUNT){
            m_filenames.removeLast();
            m_filecount--;
        }
    }

    emit dataChanged();

    QSettings settings;

    settings.beginGroup("RecentDocs");
    settings.setValue("recentdocs", m_filenames);
    settings.endGroup();
}

int RecentDocs::rowCount(const QModelIndex & /*parent*/) const
{
    return m_filecount;
}

QVariant RecentDocs::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_filenames.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_filenames.at(index.row());
    else if (role == Qt::BackgroundRole) {
        int batch = (index.row() / 100) % 2;
        if (batch == 0)
            return qApp->palette().base();
        else
            return qApp->palette().alternateBase();
    }
    return QVariant();
}
