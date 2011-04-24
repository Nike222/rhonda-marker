#include "xmllibrary.hpp"

XmlLibrary::XmlLibrary()
{
}

XmlLibrary::XmlLibrary(QString schema) :
		schemaFile(schema)
{
}

bool XmlLibrary::setSchema(QString filename)
{
	schemaFile = filename;
	return true;
}

bool XmlLibrary::ValidateXmlFile(QString filename)
{
	bool res = false;
	QUrl sch(schemaFile);
	QXmlSchema schema;
	schema.load(sch);
	if (schema.isValid()) {
		QFile file(filename);
		file.open(QIODevice::ReadOnly);
		QXmlSchemaValidator validator(schema);
		if (validator.validate(&file, QUrl::fromLocalFile(file.fileName()))) {
			res = true;
		}
	}
	return res;
}

bool XmlLibrary::load(QString filename)
{
	bool res = false;
	if (ValidateXmlFile(filename)) {
		xmlFile = filename;

		QFile f(filename);
		QString errorMsg;
		int errorLine, errorColumn;
		if (library.setContent(&f, &errorMsg, &errorLine, &errorColumn)) {
			QDomNode root = library.namedItem("object_library");

			QDomElement groups = root.namedItem("groups").toElement();
			groupsFromXml(groups);

			res = true;
		}
		library.clear();
	}
	return res;
}

void XmlLibrary::buildXml()
{
	library.clear();
	QDomProcessingInstruction instr = library.createProcessingInstruction(
		"xml", "version='1.0' encoding='UTF-8'");
	library.appendChild(instr);

	QDomElement root = library.createElement("object_library");
	library.appendChild(root);
	root.appendChild(library.createElement("objects"));

	QDomElement groups = groupsToXml(library);
	root.appendChild(groups);

	root.appendChild(library.createElement("user_types"));
}

bool XmlLibrary::save()
{
	return saveToFile(xmlFile);
}

bool XmlLibrary::saveToFile(QString filename)
{
	bool res = false;
	buildXml();

	QFile f(filename);
	if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream ts(&f);
		ts << library.toString();
		f.close();
		res = true;
	}
	return res;
}



