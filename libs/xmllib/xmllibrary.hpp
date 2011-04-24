#ifndef XMLLIBRARY_HPP
#define XMLLIBRARY_HPP

#include <QString>
#include <QList>
#include <QFile>
#include <QtXmlPatterns/QtXmlPatterns>
#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>

#include "xmllibrarygroups.hpp"

class XmlLibrary : public LibraryGroupList
{
public:
    XmlLibrary();
	XmlLibrary(QString schema);
	bool load(QString filename);
	bool save();
	bool saveToFile(QString filename);
	uint GroupCount();
	bool setSchema(QString filename);
	void print() {
		buildXml();
		qDebug() << library.toString();
	}
private:
	void buildXml();
	QString xmlFile;
	QString schemaFile;
	QDomDocument library;
	LibraryGroupList groups;
	bool ValidateXmlFile(QString filename);
};

#endif // XMLLIBRARY_HPP
