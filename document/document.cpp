#include "document.hpp"

#include "QDebug"

Document::Document(QObject *parent)
	: QObject(parent)
	, m_fps(24)
	, m_frameSpeed(1)
	, m_frameBias(0)
	, m_locked(false)
	, m_frames(NULL)
	, m_mark(NULL)
{
	emitAll();
}

Document::~Document()
{
	if (m_frames != NULL)
		delete m_frames;

	if (m_mark != NULL)
		delete m_mark;
}

void Document::setFileName(QString file_name)
{
	qDebug() << "triggered";
	if (file_name != m_fileName) {
		qDebug() << "changed";
		m_fileName = file_name;
		emit FileNameChanged(m_fileName);
		emit changed();
	}
}

void Document::setLibrary(QString library)
{
	if (!m_locked && (library != m_library)) {
		m_library = library;
		emit LibraryChanged(m_library);
	}
}

void Document::setFrameSource(QString frame_source)
{
	if (!m_locked && (frame_source != m_frameSource)) {
		m_frameSource = frame_source;
		emit FrameSourceChanged(m_frameSource);
		emit changed();
	}
}

void Document::setComment(QPlainTextEdit *edit)
{
	m_comment = edit;
}

void Document::setFPS(int fps)
{
	if (fps != m_fps) {
		m_fps = fps;
		emit FPSChanged(m_fps);
		emit changed();
	}
}

void Document::setFrameSpeed(int frame_speed)
{
	if (frame_speed != m_frameSpeed) {
		m_frameSpeed = frame_speed;
		emit FrameSpeedChanged(m_frameSpeed);
		emit changed();
	}
}

void Document::setFrameBias(int frame_bias)
{
	if (frame_bias != m_frameBias) {
		m_frameBias = frame_bias;
		emit FrameBiasChanged(m_frameBias);
		emit changed();
	}
}


void Document::create()
{
	m_locked = true;
	/* mostly full */
	emitAll();
	emit locked(true);
        emit created(m_fileName);
}

void Document::load(QString filename)
{
	m_fileName = filename;
	m_locked = true;

	/* load here */

	emitAll();
	emit locked(true);
        emit created(m_fileName);
}

void Document::save(QString filename)
{
	m_fileName = filename;

	/* save doc here */

	emit FileNameChanged(m_fileName);
}

void Document::emitAll()
{
	emit changed();
	emit FileNameChanged(m_fileName);
	emit LibraryChanged(m_library);
	emit FrameSourceChanged(m_frameSource);
	emit FPSChanged(m_fps);
	emit FrameSpeedChanged(m_frameSpeed);
	emit FrameBiasChanged(m_frameBias);
}
