#ifndef XMLLIBRARYGROUPS_HPP
#define XMLLIBRARYGROUPS_HPP

#include <QList>
#include <QtXml/QDomElement>
#include <QtXml/QDomDocument>

struct LibraryGroup
{
	LibraryGroup() :
			name("")
	{}

	LibraryGroup(uint _id, uint _parentId, QString _name) :
			id(_id),
			parentId(_parentId),
			name(_name)
	{}

	uint id;
	uint parentId;
	QString name;
};

class LibraryGroupList
{
public:
	LibraryGroupList() {}
	uint groupCount();
	LibraryGroup getGroupById(uint id);
	bool hasGroupId(uint id);
	LibraryGroup getGroupByNo(uint index);
	uint addGroup(uint parentId, QString name);
	bool setGroupName(uint id, QString name);
	bool setGroupParent(uint id, uint parent);
	bool removeGroup(uint id);	// on delete all childrens connects to parent

protected:
	QDomElement groupsToXml(QDomDocument &doc);
	uint groupsFromXml(QDomElement &e);	// result - number of loaded groups

private:
	bool _getGroupNoById(uint id, uint *no);
	bool _getGroupAttr(QDomElement &e, QString name, uint *value);
	bool _addGroup(QDomElement &e);
	QList<LibraryGroup> groupList;
};

#endif // XMLLIBRARYGROUPS_HPP
