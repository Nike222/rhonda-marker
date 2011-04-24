#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <QObject>
#include <QString>
#include "framesstore.hpp"
#include "framesmark.hpp"
#include <QPlainTextEdit>

class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(QObject *parent = 0);
	~Document();

	QString fileName();
	QString library();
	QString frameSource();
	void	setComment(QPlainTextEdit *edit);
	int		fps();
	int		frameSpeed();
	int		frameBias();

	FramesStore* frames();

signals:
	void locked(bool);
	void changed();
	void created();
	void FileNameChanged(QString);
	void LibraryChanged(QString);
	void FrameSourceChanged(QString);
	void FPSChanged(int);
	void FrameSpeedChanged(int);
	void FrameBiasChanged(int);


public slots:
	void setFileName(QString file_name);
	void setLibrary(QString library);
	void setFrameSource(QString frame_source);
	void setFPS(int fps);
	void setFrameSpeed(int frame_speed);
	void setFrameBias(int frame_bias);

	void create();
	void load(QString filename);
	void save(QString filename);

private:
	QString	m_fileName;
	QString m_library;
	QString m_frameSource;
	QPlainTextEdit	*m_comment;
	int		m_fps;
	int		m_frameSpeed;
	int		m_frameBias;
	bool m_locked;

	FramesStore	*m_frames;
	FramesMark	*m_mark;

	void emitAll();
};

#endif // DOCUMENT_HPP
