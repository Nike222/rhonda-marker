#ifndef FILECHOOSEEDIT_HPP
#define FILECHOOSEEDIT_HPP

#include <QLineEdit>

class FileChooseEdit : public QLineEdit
{
    Q_OBJECT

public:
	enum Mode {
		MSave,
		MOpen,
	};

    explicit FileChooseEdit(QWidget *parent = 0);
	void setFileMask(QString mask);
	void setCaption(QString caption);
	void setMode(Mode mode);
signals:

public slots:
	void choose();

private:
	QString m_mask;
	QString m_caption;
	enum Mode m_mode;

};

#endif // FILECHOOSEEDIT_HPP
