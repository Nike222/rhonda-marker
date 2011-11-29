<?php
/**
 * Created by JetBrains PhpStorm.
 * User: romanorlov
 * Date: 06.11.11
 * Time: 18:04
 * To change this template use File | Settings | File Templates.
 */

class XML_Library_Writer {

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

    function __construct($params) {
        $this->library  = $params['library'];
        $this->document = $params['document'];
    }
}