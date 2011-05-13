#ifndef LIBCHOOSEEDIT_HPP
#define LIBCHOOSEEDIT_HPP

#include <QComboBox>

#define MAX_RECENT_COUNT 10

class LibChooseEdit : public QComboBox
{
    Q_OBJECT

public:
    explicit LibChooseEdit(QWidget *parent = 0);
        void setFileMask(QString mask);
        void setCaption(QString caption);

signals:

public slots:
        void choose();
        void addLib(QString newlib);

private:
        QString m_mask;
        QString m_caption;
        QStringList m_recentlibs;
        int m_filecount;

};

#endif // LIBCHOOSEEDIT_HPP

