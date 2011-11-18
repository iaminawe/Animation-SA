<?php
// $Id: workflow_ng_content_forms.inc,v 1.1.2.3 2008/07/11 08:19:46 fago Exp $

/**
 * @file workflow-ng forms for CCK
 */

function workflow_ng_content_get_fields_by_type($type) {
  $fields = array();
  foreach (content_fields() as $field) {
    if ($field['type'] == $type) {
      $fields[$field['field_name']] = $field['field_name'];
    }
  }
  return $fields;
}

function workflow_ng_action_load_referenced_user_form($settings = array(), $argument_info) {
  $form = array();
  $form['field'] = array(
    '#type' => 'select',
    '#title' => t('Field'),
    '#default_value' => $settings['field'],
    '#options' => workflow_ng_content_get_fields_by_type('userreference'),
    '#description' => t('If the field has multiple values, only the first user will be loaded.'),
    '#required' => TRUE,
  );
  return $form;
}

function workflow_ng_action_load_referenced_user_submit($form_id, $form_values) {
  //returns the needed settings
  return array('field' => $form_values['field']);
}

function workflow_ng_action_load_referenced_node_form($settings = array(), $argument_info) {
  $form = array();
  $form['field'] = array(
    '#type' => 'select',
    '#title' => t('Field'),
    '#default_value' => $settings['field'],
    '#options' => workflow_ng_content_get_fields_by_type('nodereference'),
    '#description' => t('If the field has multiple values, only the first node will be loaded.'),
    '#required' => TRUE,
  );
  return $form;
}

function workflow_ng_action_load_referenced_node_submit($form_id, $form_values) {
  //returns the needed settings
  return array('field' => $form_values['field']);
}

/**
 * Action "populate a field" configuration form.
 */
function workflow_ng_action_populate_field_form($settings = array(), $argument_info) {
  $options = content_fields();
  $fields = array_keys($options);
  $fields = array_combine($fields, $fields);
  $form = array();
  $form['field_name'] = array(
    '#type' => 'select',
    '#title' => t('Field'),
    '#options' => $fields,
    '#default_value' => $settings['field_name'],
    '#description' => t('Select the machine-name of the field.'),
    '#required' => TRUE,
  );
  $sample = 'array(
  0 => array(\'value\' => value for value),
  // You\'ll usually want to stop here. Provide more values
  // if you want your \'default value\' to be multi-valued :
  1 => array(\'value\' => value for value),
  2 => ...
);

Example:
return array(0 => array(\'value\' => 10));';

    $form['default_value_php'] = array(
      '#type' => 'textarea',
      '#title' => t('Value'),
      '#default_value' => $settings['default_value_php'],
      '#rows' => 6,
      '#tree' => TRUE,
      '#description' => t('PHP code that returns a default value. Should not include &lt;?php ?&gt; delimiters. Expected format :<pre>!sample</pre>Using !link_devel\'s \'devel load\' tab on a %type content page might help you figure out the expected format.', array('!sample' => $sample, '!link_devel' => l('devel.module', 'http://www.drupal.org/project/devel'), '%type' => $type_name)),
      '#required' => TRUE,
    );

  return $form;
}

function workflow_ng_action_populate_field_validate($form_id, $form_values, $form) {
  // Add values required by _content_admin_field_validate validation.
  $field = content_fields($form_values['field_name']);
  $form_values['type_name'] = $field['type_name'];
  // Validate PHP format.
  _content_admin_field_validate($form_id, $form_values, $form);
}

function workflow_ng_action_populate_field_submit($form_id, $form_values) {
  return array('field_name' => $form_values['field_name'], 'default_value_php' => $form_values['default_value_php']);
}
