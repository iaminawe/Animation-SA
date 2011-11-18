<?php
// $Id: template.php,v 1.1.4.3 2009/02/23 11:58:56 thecrow Exp $

/**
 * @file
 * Example template.php for service_links.module
 * Use <?php print $service_links ?> to insert links in your node.tpl.php or you page.tpl.php file.
 */

function _phptemplate_variables($hook, $vars) {
  switch($hook) {
    case 'node':
    case 'page':
      if (module_exists('service_links')) {
        $vars['service_links'] = theme('links', service_links_render($vars['node'], TRUE));
      }
      break;
  }
  return $vars;
}
