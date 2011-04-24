#include "xmllibrarygroups.hpp"

uint LibraryGroupList::groupCount()
{
	 return groupList.count();
}

LibraryGroup LibraryGroupList::getGroupByNo(uint index)
{
	return groupList.at(index);
}

bool LibraryGroupList::hasGroupId(uint id)
{
	return _getGroupNoById(id, NULL);
}

LibraryGroup LibraryGroupList::getGroupById(uint id)
{
	uint no;
	LibraryGroup r;
	if (_getGroupNoById(id, &no)) {
		r = groupList.at(no);
	}
	return r;
}

bool LibraryGroupList::_getGroupNoById(uint id, uint *no) {
	LibraryGroup g;
	for (int i = 0; i < groupList.count(); i++) {
		g = groupList.at(i);
		if (g.id == id) {
			if (no != NULL)
				*no = i;
			return true;
		}
	}
	return false;
}

uint LibraryGroupList::addGroup(uint parentId, QString name)
{
	uint sid = 1;
	/* fix here to find hole in group id's
		now simply gets max */
	foreach (LibraryGroup g, groupList) {
		if (g.id >= sid)
			sid = g.id + 1;
	}
	LibraryGroup g(sid, parentId, name);
	groupList.append(g);
	return sid;
}

uint LibraryGroupList::groupsFromXml(QDomElement &e) {
	if (e.tagName() != "groups") {
		return 0;
	}
	groupList.clear();
	uint count = 0;
	QDomNode node = e.firstChild();
	while (!node.isNull()) {
		if (node.toElement().tagName() == "group") {
			QDomElement elem = node.toElement();
			if (_addGroup(elem))
				count++;
		}
		node = node.nextSibling();
	}

	return count;
}

bool LibraryGroupList::_addGroup(QDomElement &e)
{
	/* for now dont handled default values fon missing attributes */
	bool res = true;
	uint id;
	uint parent;
	res = res && _getGroupAttr(e, "id", &id);
	res = res && _getGroupAttr(e, "parent_id", &parent);
	if (res) {
		LibraryGroup g(id, parent, e.text());
		groupList.append(g);
	}
	return res;
}

bool LibraryGroupList::_getGroupAttr(QDomElement &e, QString name, uint *value)
{
	bool res = false;
	QDomAttr a = e.attributeNode(name);
	if (!a.isNull()) {
		bool ok;
		uint v = a.value().toUInt(&ok);
		if (ok) {
			*value = v;
			res = true;
		}
	}
	return res;
}

QDomElement LibraryGroupList::groupsToXml(QDomDocument &doc)
{
	QDomElement groups = doc.createElement("groups");

	foreach(LibraryGroup g, groupList) {
		QDomElement group = doc.createElement("group");
		QDomText t = doc.createTextNode(g.name);

		group.appendChild(t);
		group.setAttribute("parent_id", g.parentId);
		group.setAttribute("id", g.id);

		groups.appendChild(group);
	}

	return groups;
}

bool LibraryGroupList::setGroupName(uint id, QString name)
{
	uint no;
	bool res = false;
	if (_getGroupNoById(id, &no)) {
		groupList[no].name = name;
		res = true;
	}
	return res;
}

bool LibraryGroupList::setGroupParent(uint id, uint parent)
{
	uint no;
	bool res = false;
	if (_getGroupNoById(id, &no) && _getGroupNoById(parent, NULL)) {
		groupList[no].parentId = parent;
		res = true;
	}
	return res;
}

bool LibraryGroupList::removeGroup(uint id)
{
	bool res = false;
	uint no;
	if (_getGroupNoById(id, &no)) {
		uint p = groupList[no].parentId;
		groupList.removeAt(no);
		res = true;
		uint c = groupList.count();
		for(uint i = 0; i < c; i++) {
			if (groupList[i].parentId == id)
				groupList[i].parentId = p;
		}
	}
	return res;
}
