<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Welcome extends CI_Controller {


	public function index()
	{
        $this->load->library('xml_libraries');

        $library = $this->xml_libraries->getLibrary('library.xml');
        $group = $library->getReader()->getGroupById(2);
        $objects = $library->getReader()->getGroupObjects($group);
        $path = $objects[0]->getNodePath();
        echo $library->getReader()->getObjectByPath($path)->getNodePath();

	}
}

/* End of file welcome.php */
/* Location: ./application/controllers/welcome.php */