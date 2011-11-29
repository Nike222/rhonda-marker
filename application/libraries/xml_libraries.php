<?php

class XML_Libraries {

    /**
     * Codeigniter global
     *
     * @var null
     */
    private $ci = null;

    /**
     * Libraries directory map
     *
     * @var array
     */
    private $map = null;

    /**
     * Libraries docRoot
     *
     * @var string
     */
    private $librariesPath = null;

    /**
     * XML schema file path
     *
     * @var string
     */
    private $schema = null;

    function __construct() {

        $this->ci =& get_instance();

        $this->ci->config->load('application', TRUE);
        $this->librariesPath = $this->ci->config->item('xml_libraries', 'application');
        $this->schema  = $this->ci->config->item('xml_schema',  'application');

        $this->ci->load->helper('directory');
        $this->map = directory_map($this->librariesPath);
        $this->filterNonXMLfiles();
    }

    /**
     * returns map of application XML libraries
     *
     * @return array|null
     */
    public function getMap() {
        return $this->map;
    }

    /**
     * creates and returns XMLLibrary from $libraryName
     * NULL if $libraryName doesn't exists
     *
     * @param $libraryFile
     * @return null|XML_Library
     */
    public function getLibrary($libraryFile) {
        if (!in_array("$libraryFile", $this->map)) {
            return null;
        }

        // dots - not OK
        $libraryName = trim($libraryFile, '.');

        if (!isset($this->ci->$libraryName)) {
            $params = array(
                'libraryPath' => $this->librariesPath."$libraryFile",
                'schemaPath' => $this->schema,
            );
            $this->ci->load->library('xml_library', $params, $libraryName);
        }

        return $this->ci->$libraryName;
    }

    /**
     * function filters libraries map from all non XML files
     *
     */
    private function filterNonXMLfiles() {
        $this->map = array_filter(directory_map(FCPATH."var/libraries"),
                    function($var){
                        return preg_match('/^.*\.xml$/',$var);
        });
    }
}
?>