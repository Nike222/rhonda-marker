<?php
/**
 * Created by JetBrains PhpStorm.
 * User: romanorlov
 * Date: 06.11.11
 * Time: 18:01
 * To change this template use File | Settings | File Templates.
 */

class XML_Library_Reader {

    /**
     * @var XML_Library instance
     *
     */
    private $library = null;

    /**
     * @var DOMDocument instance
     *
     */
    private $document = null;

    /**
     * Library Reader Constructor
     *
     * @param $params
     */
    function __construct($params) {
        $this->library  = $params['library'];
        $this->document = $params['document'];
    }

    /**
     * Returns
     *
     * @return DOMNodeList
     */
    public function getGroups() {
        $groups = $this->document->getElementsByTagName('group');
        return $groups;
    }

    /**
     * Returns all group with root parent
     *
     * @return DOMNodeList
     */
    public function getFirstLevelGroups() {
        $groups = $this->document->getElementsByTagName('group');
        foreach ($groups as &$group) {
            if ($group->attributes->getNamedItem('parent_id') != 0)
                unset($group);
        }
        return $groups;
    }

    /**
     * Returns group by its ID
     *
     * @param $id
     * @return DOMNodeList|null
     */
    public function getGroupById($id) {
        $groups = $this->getGroups();
        foreach ($groups as $group) {
            if ($group->attributes->getNamedItem('id')->nodeValue == $id) {
                return $group;
            }
        }
        return NULL;
    }

    /**
     * Returns group child-objects and groups
     *
     * @param DOMNode $parentGroup
     * @return DOMNode[]
     */
    public function getGroupChildren(DOMNode $parentGroup) {
        $childGroups = $this->getGroupChildGroups($parentGroup);
        $childObjects = $this->getGroupChildObjects($parentGroup);
        return array_merge($childGroups, $childObjects);
    }

    /**
     * Returns child objects
     *
     * @param DOMNode $parentGroup
     * @return DOMNode[]
     */
    public function getGroupChildObjects(DOMNode $parentGroup) {
        $groupId = $parentGroup->attributes->getNamedItem('id')->nodeValue;
        $objects = $this->document->getElementsByTagName('object');
        $childObjects = array();
        foreach ($objects as &$object) {
            if ($object->attributes->getNamedItem('group')->nodeValue == $groupId ) {
                $childObjects[] = $object;
            }
        }
        return $childObjects;
    }

    /**
     * Returns child groups
     *
     * @param DOMNode $parentGroup
     * @return DOMNode[]
     */
    public function getGroupChildGroups(DOMNode $parentGroup) {
        $groupId = $parentGroup->attributes->getNamedItem('id')->nodeValue;
        $groups = $this->document->getElementsByTagName('group');
        $childGroups = array();
        foreach ($groups as &$group) {
            if ($group->attributes->getNamedItem('parent_id')->nodeValue == $groupId ) {
                $childGroups[] = $group;
            }
        }
        return $childGroups;
    }

    /**
     * Returns object by its path
     *
     * @param $path
     * @return DOMNode|null
     */
    public function getObjectByPath($path) {
        $path = array_slice(explode('/',$path), 2);
        $element = $this->document;
        foreach ($path as $dir) {
            $element = $this->_getChildByTagName($element, $dir);
        }
        return $element;
    }

    /**
     * Returns node child by its tad name
     * like 'object[1]'
     *
     * @param $parent
     * @param $childName
     * @return mixed
     */
    protected function _getChildByTagName($parent, $childName) {
        $childIndex = 0;
        if (preg_match('/\w+\[\d+\]/', $childName)) {
            $childIndex = preg_replace('/(\w+)\[(\d+)\]/','${2}', $childName) - 1;
            $childName  = preg_replace('/(\w+)\[(\d+)\]/','${1}', $childName);
        }
        return
            $parent->getElementsByTagName($childName)->item($childIndex);
    }
}