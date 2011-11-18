<?php
// $Id: theme.inc,v 1.2.2.4 2009/01/08 04:22:22 michellec Exp $

/**
 * @file
 * Holds theme and preprocess functions.
 */

/**
 * Theme function wrapper around D6 style preprocess function.
 */
function theme_advanced_profile_visitors($account) {
  $variables['account'] = $account;
  template_preprocess_advanced_profile_visitors($variables);
  return _phptemplate_callback("advanced_profile_visitors", $variables, array("advanced_profile_visitors"));
}

function template_preprocess_advanced_profile_visitors(&$variables) {
  $visitors = advanced_profile_visitors($variables['account']->uid);
    
  if (!empty($visitors)) {
    $variables['visitors'] = theme_item_list($visitors);
  }
  else {
    $variables['visitors'] = t("No recent visitors.");
  }
}

/**
 * Themes the user_list view.
 */
function phptemplate_views_view_list_user_list($view, $nodes, $type) {
  $fields = _views_get_fields();

  $taken = array();

  // Set up the fields in nicely named chunks.
  foreach ($view->field as $id => $field) {
    $field_name = $field['field'];
    if (isset($taken[$field_name])) {
      $field_name = $field['queryname'];
    }
    $taken[$field_name] = true;
    $field_names[$id] = $field_name;
  }

  // Set up some variables that won't change.
  $base_vars = array(
    'view' => $view,
    'view_type' => $type,
  );

  foreach ($nodes as $i => $node) {
    $vars = $base_vars;
    $vars['node'] = $node;
    $vars['count'] = $i;
    $vars['stripe'] = $i % 2 ? 'even' : 'odd';
    foreach ($view->field as $id => $field) {
      $name = $field_names[$id];
      $vars[$name] = views_theme_field('views_handle_field', $field['queryname'], $fields, $field, $node, $view);
      if (isset($field['label'])) {
        $vars[$name . '_label'] = $field['label'];
      }
    }
    $items[] = _phptemplate_callback('advanced_profile_view_user-list', $vars);
  }
  if ($items) {
    advanced_profile_add_css();
    return implode("", $items);
  }
}