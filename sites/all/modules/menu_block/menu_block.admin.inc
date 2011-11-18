<?php
// $Id: menu_block.admin.inc,v 1.5 2008/08/04 19:56:56 johnalbin Exp $

/**
 * Display the settings form for Menu block.
 *
 * @return
 *   The form array.
 */
function _menu_block_settings() {
  $form = array();
  $form['menu_block_enabled_blocks'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Enable the following blocks of menu trees'),
    '#default_value' => variable_get('menu_block_enabled_blocks', array()),
    '#options'       => array(),
    '#description'   => t('Only enabled blocks will appear on the <a href="!url">administer blocks page</a>.', array('!url' => url('admin/build/block'))),
  );
  foreach (variable_get('menu_block_enabled_blocks', array()) AS $delta => $enabled) {
    $form['menu_block_enabled_blocks']['#options'][$delta] = _menu_block_format_title($delta);
  }
  $form['menu_block_enabled_blocks']['#options']['-1'] = '<em>' . t('Add a new unconfigured menu block.') . '</em>';

  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  return $form;
}

/**
 * Implments submit handler for menu_block_settings form.
 */
function _menu_block_settings_submit($form_id, $form_values) {
  $enabled_blocks = $form_values['menu_block_enabled_blocks'];

  // Optionally add a new unconfigured block.
  if ($enabled_blocks['-1']) {
    $key = count($enabled_blocks); // Auto-increment.
    $enabled_blocks[$key] = $key;
  }
  unset($enabled_blocks['-1']);

  // Save the enabled blocks.
  variable_set('menu_block_enabled_blocks', $enabled_blocks);
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Returns the 'list' $op info for hook_block().
 */
function _menu_block_block_list() {
  foreach (variable_get('menu_block_enabled_blocks', array()) AS $delta => $enabled) {
    if ($enabled) {
      $blocks[$delta]['info'] = _menu_block_format_title($delta);
    }
  }
  return $blocks;
}

/**
 * Return the title of the block.
 *
 * @param $delta
 *   int The delta of the menu block
 * @return
 *   string The title of the block
 */
function _menu_block_format_title($delta) {
  $mid = variable_get("menu_block_{$delta}_mid", NULL);
  if (is_null($mid)) {
    $title = t('Unconfigured menu block');
  }
  else {
    $level = variable_get("menu_block_{$delta}_level", 1);
    $depth = variable_get("menu_block_{$delta}_depth", 0);
    $menus = menu_get_root_menus();
    // Show the configured levels in the block info
    $replacements = array('@menu_name' => $menus[$mid], '@level1' => $level, '@level2' => $level + $depth - 1);
    if ($depth == 1) {
      $title = t('@menu_name (level @level1)', $replacements);
    }
    elseif ($depth) {
      $title = t('@menu_name (levels @level1-@level2)', $replacements);
    }
    else {
      $title = t('@menu_name (levels @level1+)', $replacements);
    }
  }
  return $title;
}

/**
 * Returns the 'configure' $op info for hook_block().
 */
function _menu_block_block_configure($delta) {

  $form['mid'] = array(
    '#type' => 'select',
    '#title' => t('Menu'),
    '#default_value' => variable_get("menu_block_{$delta}_mid", 1),
    '#options' => array(),
    '#description' => t('The tree (or list) of links will be taken from this menu.'),
  );
  foreach (menu_get_root_menus() AS $mid => $title) {
    $form['mid']['#options'][$mid] = $title;
  }
  $form['level'] = array(
    '#type' => 'select',
    '#title' => t('Starting level of menu tree'),
    '#default_value' => variable_get("menu_block_{$delta}_level", 1),
    '#options' => array(
      '1'  => t('1st level (primary)'),
      '2'  => t('2nd level (secondary)'),
      '3'  => t('3rd level (tertiary)'),
      '4'  => t('4th level'),
      '5'  => t('5th level'),
      '6'  => t('6th level'),
      '7'  => t('7th level'),
      '8'  => t('8th level'),
      '9'  => t('9th level'),
      '10' => t('10th level'),
    ),
    '#description' => t("Blocks that start with the 2nd level or deeper will only be visible when the active menu item is in the block's tree. Blocks that start with the 1st level will always be visible."),
  );
  $form['depth'] = array(
    '#type' => 'select',
    '#title' => t('Maximum depth of menu tree'),
    '#default_value' => variable_get("menu_block_{$delta}_depth", 0),
    '#options' => array(
      '1'  => '1',
      '2'  => '2',
      '3'  => '3',
      '4'  => '4',
      '5'  => '5',
      '6'  => '6',
      '7'  => '7',
      '8'  => '8',
      '9'  => '9',
      '10' => '10',
      '0'  => 'Unlimited',
    ),
    '#description' => t('Trees with a maximum depth of 1 will be styled as a menu list, i.e. theme_menu_block_list() instead of theme_menu_block_tree().'),
  );
  $form['expanded'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expand all children'),
    '#default_value' => variable_get("menu_block_{$delta}_expanded", 0),
    '#description' => t('All sub-menus of this menu will be expanded.'),
  );
  return $form;
}

/**
 * Returns the 'save' $op info for hook_block().
 */
function _menu_block_block_save($delta, $edit) {
  variable_set("menu_block_{$delta}_mid", $edit['mid']);
  variable_set("menu_block_{$delta}_level", $edit['level']);
  variable_set("menu_block_{$delta}_depth", $edit['depth']);
  variable_set("menu_block_{$delta}_expanded", $edit['expanded']);
}
