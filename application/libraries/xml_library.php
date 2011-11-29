<?php


class XML_Library {

    /**
     * Codeidniter global
     *
     * @var null
     */

    private $ci = null;
    /**
     * Instance to DOMDocument
     * @var null
     */
    private $document = null;

    /**
     * Schema validation errors
     *
     * @var null
     */
    private $errors = null;

    /**
     * Path to xml-file
     *
     * @var null
     */
    private $libraryPath = null;

    /**
     * Path to xsd-file
     *
     * @var null
     */
    private $schemaPath = null;

    /**
     * Instance to library reader
     *
     * @var null
     */
    private $reader = null;

    /**
     * Instance to library writer
     *
     * @var null
     */
    private $writer = null;

    /**
     * XML_Library constructor
     * $params:
     *  libraryPath - path to library xml-file
     *  schemaPath  - path to library schema-file
     *
     * @param $params
     */
    function __construct($params) {

        if (!file_exists($params['libraryPath']) || !file_exists($params['schemaPath'])) {
            return null;
        }

        $this->ci =& get_instance();

        libxml_use_internal_errors(true);
        $this->libraryPath = $params['libraryPath'];
        $this->schemaPath = $params['schemaPath'];

        $this->document = new DOMDocument();
        $this->document->load($this->libraryPath);
        $this->document->schemaValidate($this->schemaPath);
        $this->errors = libxml_get_errors();

        $this->ci->load->library('xml_library_reader', array('library' => $this, 'document' => $this->document), 'reader');
        $this->ci->load->library('xml_library_writer', array('library' => $this, 'document' => $this->document), 'writer');
    }

    /**
     * saves filechanges if there is no validation errors
     *
     * @return bool|int
     */
    public function save() {
        if (!$this->document->schemaValidate($this->schemaPath)) {
            return FALSE;
        }

        return $this->document->save($this->libraryPath);
    }

    /**
     * returns schemaValidation errors
     *
     * @return array|null
     */
    public function getValidationErrors() {
        return $this->errors;
    }

    /**
     * returns last LibXMLError error
     *
     * @return LibXMLError
     */
    public function getLastError() {
        return libxml_get_last_error();
    }

    /**
     * returns library reader class
     *
     * @return XML_Library_Reader
     */
    public function getReader() {
        return $this->ci->reader;
    }

    /**
     * returns library writer class
     *
     * @return XML_Library_Writer
     */
    public function getWriter() {
        return $this->ci->writer;
    }
}
?>