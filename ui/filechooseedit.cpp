#include "filechooseedit.hpp"

#include <QDebug>
#include <QFileDialog>

FileChooseEdit::FileChooseEdit(QWidget *parent)
	: QLineEdit(parent)
	, m_mode(MSave)

{
}

void FileChooseEdit::setFileMask(QString mask)
{
	m_mask = mask;
}

void FileChooseEdit::setCaption(QString caption)
{
	m_caption = caption;
}

void FileChooseEdit::choose()
{
	QString file;
	if (m_mode == MSave) {
		file = QFileDialog::getSaveFileName(this, m_caption, "", m_mask, 0, 0);
	} else {
		file = QFileDialog::getOpenFileName(this, m_caption, "", m_mask, 0, 0);
	}

	if (!file.isEmpty()) {
		setText(file);
	}


//	fileName = QFileDialog::getOpenFileName(this,
//		 tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));

	//auto emit TextChanged;
}

void FileChooseEdit::setMode(Mode mode)
{
	m_mode = mode;
}
