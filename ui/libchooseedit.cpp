#include "libchooseedit.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QSettings>

LibChooseEdit::LibChooseEdit(QWidget *parent)
        : QComboBox(parent)
{
    QSettings settings;

    settings.beginGroup("RecentLibs");
    m_recentlibs = settings.value("recentlibs", QStringList()).toStringList();
    settings.endGroup();

    if (m_recentlibs.count() > MAX_RECENT_COUNT)
        m_recentlibs.erase(m_recentlibs.begin()+MAX_RECENT_COUNT, m_recentlibs.end());

    m_filecount = m_recentlibs.count();
    if (m_filecount > 0){
        addItems(m_recentlibs);
        emit editTextChanged(currentText());
        qDebug() << currentText();
    }
}

void LibChooseEdit::setFileMask(QString mask)
{
        m_mask = mask;
}

void LibChooseEdit::setCaption(QString caption)
{
        m_caption = caption;
}

void LibChooseEdit::choose()
{
        QString file;

        file = QFileDialog::getOpenFileName(this, m_caption, "", m_mask, 0, 0);

        if (!file.isEmpty()) {
                addItem(file);
                addLib(file);
                emit editTextChanged(file);
            }
}

void LibChooseEdit::addLib(QString newlib)
{
    if (m_recentlibs.contains(newlib)){
        m_recentlibs.move(m_recentlibs.indexOf(newlib), 0);
    } else {
        m_recentlibs.prepend(newlib);
        m_filecount++;
        if (m_filecount > MAX_RECENT_COUNT){
            m_recentlibs.removeLast();
            m_filecount--;
        }
    }

    QSettings settings;

    settings.beginGroup("RecentLibs");
    settings.setValue("recentlibs", m_recentlibs);
    settings.endGroup();
}
