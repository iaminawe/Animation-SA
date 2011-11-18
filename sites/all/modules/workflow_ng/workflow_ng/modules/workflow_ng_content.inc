<?php
// $Id: workflow_ng_content.inc,v 1.1.2.4 2008/07/11 08:19:46 fago Exp $

/**
 * @file workflow-ng integration for CCK
 */

/**
 * Implementation of hook_module_info
 */
function content_module_info() {
  return array(
    'cck_workflow_ng_forms' => array(
      'file' => 'workflow_ng_content_forms.inc',
      'file path' => drupal_get_path('module', 'workflow_ng') .'/modules/',
  ),
  );
}

/**
 * Implementation of hook_action_info()
 */
function content_action_info() {
  $info = array();
  if (module_exists('userreference')) {
    $info['workflow_ng_action_load_referenced_user'] = array(
      '#label' => t('Load a referenced user'),
      '#arguments' => array(
        'node' => array('#entity' => 'node', '#label' => t('Content containing the user reference field')),
      ),
      '#new arguments' => array(
        'referenced_user' => array('#entity' => 'user', '#label' => t('Referenced user')),
      ),
      '#module' => 'CCK',
    );
  }
  if (module_exists('nodereference')) {
    $info['workflow_ng_action_load_referenced_node'] = array(
      '#label' => t('Load a referenced node'),
      '#arguments' => array(
        'node' => array('#entity' => 'node', '#label' => t('Content containing the node reference field')),
      ),
      '#new arguments' => array(
        'referenced_node' => array('#entity' => 'node', '#label' => t('Referenced content')),
      ),
      '#module' => 'CCK',
    );
    $info['workflow_ng_action_populate_field'] = array(
      '#label' => t('Populate a field'),
      '#arguments' => array(
        'node' => array('#entity' => 'node', '#label' => t('Content')),
      ),
      '#description' => 'Populate a CCK field with a PHP-returned value. You should make sure that the used field exists in the given content type.',
      '#module' => 'CCK',
    );
  }
  return $info;
}

function workflow_ng_action_load_referenced_user($node, $settings) {
  if ($uid = $node->{$settings['field']}[0]['uid']) {
    $user = user_load(array('uid' => $uid));
    return array('#new arguments' => array('referenced_user' => $user));
  }
}

function workflow_ng_action_load_referenced_node($node, $settings) {
  if ($nid = $node->{$settings['field']}[0]['nid']) {
    return array('#new arguments' => array('referenced_node' => node_load(array('nid' => $nid))));
  }
}

/**
 * Action: populate a field.
 */
function workflow_ng_action_populate_field($node, $settings) {
  //Get information about the field.
  $field = content_fields($settings['field_name'], $node->type);

  // Taken from function content_default_value().
  ob_start();
  $result = eval($settings['default_value_php']);
  ob_end_clean();

  if (!empty($field) && is_array($result)) {
    $node->$settings['field_name'] = $result;
    return array('node' => $node);
  }
}
