<?php

/*
 * Implementation of hook_pageroute_info()
 */
function pageroute_pageroute_info() {
  return array(
    'add' => array('name' => t('Node adding form'), 'base' => 'pageroute', 'default_target' => PAGEROUTE_FORWARD),
    'edit' => array('name' => t('Node edit form'), 'base' => 'pageroute', 'default_target' => PAGEROUTE_FORWARD),
    'view' => array('name' => t('Node display'), 'base' => 'pageroute', 'default_target' => PAGEROUTE_FORWARD),
    'manage' => array('name' => t('Node management'), 'base' => 'pageroute', 'default_target' => PAGEROUTE_CURRENT),
    'user_edit' => array('name' => t('User edit form'), 'base' => 'pageroute', 'default_target' => PAGEROUTE_FORWARD),
  );
}

/*
 * Returns the node adding form for the configured node type
 */
function pageroute_page_add($route, $page, $form, $content_type = NULL) {
  $type = isset($content_type) ? $content_type : $page->options['content-type'];

  // If a node type has been specified, validate its existence.
  if (node_access('create', $type)) {
    $account = user_load(array('uid' => pageroute_page_get_uid($page, 'administer nodes')));
    // Initialize settings:
    $node = array('uid' => $account->uid, 'name' => $account->name, 'type' => $type);

    $form['page_form'] = array(
      '#type' => 'subform',
      '#id' => $type .'_node_form',
      '#arguments' => array($node),
      '#data_separation' => FALSE,
    );
    return $form;
  }
  else {
    drupal_access_denied();
    pageroute_exit_now();
  }
}

/*
 * Returns the node edit form for the configured node type or the give node id
 * 
 * @param $argument_index Tells the function, which route argument shall be used for getting the node id.
 *   This allows reusing this function from other pages, e.g. the node management page. If nothing is
 *   given the function will use $nid page argument
 */
function pageroute_page_edit($route, $page, $form, $nid = NULL) {
  
  $task = pageroute_page_arg($page, 0);
  if ($task == 'delete') {
    //we need to show the delete subpage
    $page->arg_offset++;
  }
  $nid = isset($nid) ? $nid : pageroute_page_get_nid($page);  

  if (empty($nid) && $page->options['content-type']) {
    return pageroute_page_add($route, $page, $form);
  }
  else if (!is_numeric($nid) || !($node = node_load($nid)) ) {        
    drupal_not_found();
    pageroute_exit_now();
  }

  //do we need to show the delete confirm form?
  if ($task == 'delete') {
    return pageroute_node_delete_confirm($node, $page, $form);
  }

  //show edit form
  if ($_POST['op'] == t('Delete')) {
    drupal_goto(pageroute_create_path($page, $page->name .'/delete'), pageroute_get_new_destination($page->route));
  }
  if (node_access('update', $node)) {
    //load the node edit form
    $form['page_form'] =  array(
      '#type' => 'subform',
      '#id' => $node->type .'_node_form',
      '#arguments' => array($node),
      '#data_separation' => FALSE,
    );
    return $form;
  }
  else {
    drupal_access_denied();
    pageroute_exit_now();
  }
}     

/*
 * Returns the node display for the configured node
 */
function pageroute_page_view($route, $page, $form) {
  if (!$page->options['nid'] && pageroute_page_get_nid($page)) {
    $page->options['nid'] = pageroute_page_get_nid($page);
  }
  if ($page->options['nid']) {
    $node = node_load($page->options['nid']);
    if ($node->nid && node_access('view', $node)) {
      if (empty($page->title)) {
        drupal_set_title(check_plain($node->title));
      }
      node_tag_new($node->nid);
      $form['page_form'] = array('#value' => node_view($node, FALSE, TRUE, FALSE));
      return $form;
    }
    else if (db_result(db_query('SELECT nid FROM {node} WHERE nid = %d', $page->options['nid']))) {
      drupal_access_denied();
      pageroute_exit_now();
    }
  }
  drupal_not_found();
  pageroute_exit_now();
}


/*
 * Implementation of hook_nodeapi
 */
function pageroute_nodeapi(&$node, $op, $teaser = NULL, $page = NULL) {
  global $page;
  //if a node is created with the page type node edit or node add,
  //we append the new nid as argument to the pageroute
  if ($op == 'insert' && isset($page) && in_array($page->type, array('add', 'edit'))) {
    if (!pageroute_arg($page->route, $page->arg_offset)) {
      pageroute_add_new_arg($page->route, $node->nid, $page->arg_offset);
    }
  }
}

/*
 * Shows a node management page for the given content type
 * It determines itself what has to be displayed (overview, add/edit/delete form).
 */
function pageroute_page_manage($route, $page, $form) {
  $arg = pageroute_arg($route, 1);

  switch ($arg) { 
    case 'add':
      $page->arg_offset = 2;
      return pageroute_page_add($route, $page, $form);

    case 'edit':
      $page->arg_offset = 3;
      return pageroute_page_edit($route, $page, $form, pageroute_arg($route, 2));

    case 'delete':
      if (!is_numeric(pageroute_arg($route, 2)) || !($node = node_load(pageroute_arg($route, 2)))) {
        drupal_not_found();
        pageroute_exit_now();
      }
      $page->arg_offset = 3;
      return pageroute_node_delete_confirm($node, $page, $form);

    default:
      if (!$arg || is_numeric($arg)) {
        return pageroute_page_manage_overview($route, $page, $form, $page->options['content-type']);
      }
      drupal_not_found();
      pageroute_exit_now();
  }
}

/*
 * Shows the overview of node management page
 */
function pageroute_page_manage_overview($route, $page, $form, $content_type) {
  $result = db_query(db_rewrite_sql("
    SELECT n.nid FROM {node} n
    WHERE n.type = '%s' AND n.uid = %d AND n.status > 0
    ORDER BY n.created
  "), $content_type, pageroute_page_get_uid($page));

  $i = 1; $output = '';
  while ($row = db_fetch_object($result)) {
    $node = node_load($row->nid);

    $buttons = array();
    if (node_access('update', $node)) {
      $buttons[] = t('Edit');
    }
    if (node_access('delete', $node)) {
      $buttons[] = t('Delete');
    }

    if (count($buttons)) {
      $form[$node->nid]['buttons'] = theme('pageroute_page_manage_buttons', $node, $i, $buttons);
      $buttons = drupal_render($form[$node->nid]['buttons']);
    }
    $form['node_list'][$node->nid] = array('#value' => theme('pageroute_page_manage_node', $node, $i++, $buttons));
  }

  //there are no nodes yet
  if ($i == 1) {
    if ($page->options['empty']['force_add']) {
      //mark that we have shown the empty add page, so that we can alter the redirect target correctly
      //and we have to apply the add form settings now
      $page->empty_add = TRUE;
      $form['target']['#value'] = PAGEROUTE_FORWARD;
      //re-add the buttons with the new settings
      unset($form['buttons']);
      pageroute_add_buttons($form, $page, 'page_op');
      return pageroute_page_add($route, $page, $form);
    }
    $types = node_get_types('names');
    $form['output'] = theme('pageroute_page_manage_empty', $types[$content_type], $page);
    $add_button = $page->options['empty']['add_button'];
  }
  else {
    $add_button = $page->options['add_button'];
    //remember all possible node ids for the target hook
    $form['node_ids'] = array('#type' => 'value', '#value' => array_keys($form['node_list']));
  }

  //add buttons
  if ($add_button && (!module_exists('nodefamily') || nodefamily_content_type_get_max($content_type) != $i-1 || $i == 1)) {
    $form['add_button'] = theme('pageroute_page_manage_add_button', $content_type, t($add_button));
  }

  return $form;
}


/*
 * Theme the display of a pageroute node management page
 */
function theme_pageroute_page_manage_node(&$node, $number, &$buttons) {

  $output = node_view($node, FALSE, TRUE, FALSE);
  $output .= $buttons;

  $title = check_plain(node_get_types('name', $node->type));
  if (!(module_exists('nodefamily') && nodefamily_content_type_get_max($node->type) == 1)) {
    //only append the number if it's possible to add more than one node
    $title .= ' '. $number;
  }

  $fieldset = array(
    '#title' => $title,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#children' => $output,
  );
  return theme('fieldset', $fieldset);
}

/*
 * Theme the display of the edit/delete buttons of an existing node
 */
function theme_pageroute_page_manage_buttons($node, $number, $buttons) {
  
  foreach ($buttons as $key => $name) {
    $form[$name]['#attributes']['class'] = 'pageroute-'. $name;
    $form[$name]['#type'] = 'submit';
    $form[$name]['#value'] = $name;
    $form[$name]['#name'] = 'manage_op_'. $node->nid;
    $form[$name]['#weight'] = $key;
  }
  $form['#prefix'] = '<span class="pageroute_manage_buttons">';
  $form['#suffix'] = '</span>';        

  return $form;
}

/*
 * Theme the add node button
 */
function theme_pageroute_page_manage_add_button($content_type, $label) {
  
  $form_element['#attributes']['class'] = 'pageroute-add';
  $form_element['#type'] = 'submit';
  $form_element['#name'] = 'manage_op_add';
  $form_element['#value'] = $label;
  $form_element['#prefix'] = '<span class="pageroute_manage_add_button">';
  $form_element['#suffix'] = '</span>';
  return $form_element;
}

/*
 * Themes an empty node list
 */
function theme_pageroute_page_manage_empty($type_name, $page) {
  $fieldset = array(
    '#type' => 'fieldset',
    '#title' => check_plain($type_name),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#children' => '<p>'. t('There is no @type.', array('@type' => $type_name)). '</p>',
  );
  return $fieldset;
}

/*
 * Implementation of pageroute hook page_target
 */
function pageroute_page_manage_target($route, $page, $form_values) {
  if ($form_values['page_op']) {
    $arg = pageroute_arg($route, 1);
    if (!isset($page->empty_add) && (!$arg || is_numeric($arg))) {
      return; //use the default behaviour
    }
    else {
      //default to route back to the overview page
      return PAGEROUTE_CURRENT;
    }
  }
  
  // determine if a node edit/delete button has been pressed
  if (isset($form_values['node_ids'])) {
    foreach ($form_values['node_ids'] as $nid) {
      if ($form_values['manage_op_'. $nid]) {
        if ($form_values['manage_op_'. $nid] == t('Edit')) {
          return pageroute_create_path($page, $page->name .'/edit/'. $nid);
        }
        if ($form_values['manage_op_'. $nid] == t('Delete')) {
          return pageroute_create_path($page, $page->name .'/delete/'. $nid);
        }
      }
    }
  }
  // determine if a node add button has been pressed
  if ($form_values['manage_op_add']) {
    return pageroute_create_path($page, $page->name .'/add');
  }
}

/*
 * Implementation of pageroute hook page_options
 */
function pageroute_page_manage_options($route, $page) {
  $arg = pageroute_arg($page->route, 1);
  if ($page->empty_add) {
    //we are showing the empty add page
    $page->options['add']['cancel'] = $page->options['empty']['cancel'];
    return $page->options['add'] + array('show_route_buttons' => TRUE);
  }
  switch ($arg) {
    case 'add':
      return $page->options['add'] + array('show_route_buttons' => TRUE);
    case 'edit':
      return $page->options['edit'] + array('show_route_buttons' => TRUE);
    default:
      return $page->options;
  }
}

/*
 * Provide an extra delete page to keep control about the destination parameter.
 */
function pageroute_node_delete_confirm($node, $page, $form) {

  if (node_access('delete', $node)) {
    unset($form['buttons']);
    unset($form['tabs']);

    $path = array();
    $path['query'] = pageroute_get_new_destination($page->route);
    $path['path'] = pageroute_get_path($page);

    $form['nid'] = array('#type' => 'value', '#value' => $node->nid);
    $form['#submit'] = array('pageroute_node_delete_confirm_submit' => array()) + $form['#submit'];
    $form['target']['#value'] = PAGEROUTE_CURRENT;

    return confirm_form($form,
      t('Are you sure you want to delete %title?', array('%title' => $node->title)),
      $path,
      t('This action cannot be undone.'), t('Delete'), t('Cancel')
    );
  }
  drupal_access_denied();
  pageroute_exit_now();
}

function pageroute_node_delete_confirm_submit($form_id, &$form_values) {
  global $page;

  if ($form_values['confirm']) {
    node_delete($form_values['nid']);
    if (pageroute_page_arg($page, 0) == $form_values['nid']) {
      pageroute_add_new_arg($page->route, 0, $page->arg_offset);
    }
  }
}



/*
 * Implementation of page type user_edit
 */
function pageroute_page_user_edit($route, $page, $form) {
  $form['user'] = array(
    '#type' => 'subform',
    '#id' => 'pageroute_page_user_edit_subform',
    '#arguments' => array($page),
    '#data_separation' => FALSE,
  );
  return $form;
}

/*
 * User edit is currently not programmatically submitable,
 * so we simulate it
 */
function pageroute_page_user_edit_subform($page) {
  global $user;

  $account = user_load(array('uid' => pageroute_page_get_uid($page, 'administer users')));
  if (!$account->uid) {
    drupal_not_found();
    pageroute_exit_now();
  }
  $edit = $_POST['op'] ? $_POST['edit'] : (array)$account;
  
  $form = array();
  $form['#base'] = 'user_edit';
  $form['user'] = _user_forms($edit, $account, $page->options['category']);
  $form['user']['_category'] = array('#type' => 'value', '#value' => $page->options['category']);
  $form['user']['_account'] = array('#type' => 'value', '#value' => $account);
  return $form;
}


/*
 * ui part
 * the following functions are page ui hook implementations,
 * which define page type specific form items
 */

/*
 * These form fields are quite common for node forms, so page
 * types, which are also displaying node forms can use it
 * @param $delete Wheter the "delete checkbox" should be added
 */
function pageroute_pages_node_ui($route, $page, &$form, $type, $delete = TRUE) {
  $form['options']['preview'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display preview button'),
    '#default_value' => $page->options['preview'],
    '#weight' => 5,        
  );
  $form['options']['submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display submit button'),
    '#default_value' => isset($page->options['submit']) ? $page->options['submit'] : 1,
    '#weight' => 5,        
  );
  if ($delete) {
    $form['options']['nodelete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Never display the delete button'),
      '#default_value' => isset($page->options['nodelete']) ? $page->options['nodelete'] : 1,
      '#weight' => 5,        
    );
  }
}

function pageroute_page_add_ui($route, $page, &$form, $type) {
  $form['options']['content-type'] = array(
    '#type' => 'select',
    '#title' => t('Content type'),
    '#options' => node_get_types('names'),
    '#required' => TRUE,
    '#default_value' => $page->options['content-type'],
    '#weight' => 2,
  );
  if (!isset($page->options['cancel'])) {
    //we default to show the cance button on add node forms
    $form['options']['cancel']['#default_value'] = t('Cancel');
  }
  pageroute_pages_node_ui($route, $page, $form, $type, FALSE);
}

function pageroute_page_edit_ui($route, $page, &$form, $type) {
  $form['options']['content-type'] = array(
    '#type' => 'select',
    '#title' => t('Content type for new nodes'),
    '#options' => array('' => '') + node_get_types('names'),
    '#default_value' => $page->options['content-type'],
    '#weight' => 2,
    '#description' => t('If there is no node id in the URL, a node add form '.
                        'for this content-type will be displayed. '.
                        'Leave it empty to show the Page Not Found error instead.'),
  );
  pageroute_pages_node_ui($route, $page, $form, $type);
}

function pageroute_page_view_ui($route, $page, &$form, $type) {
  $form['options']['nid'] = array(
    '#type' => 'textfield',
    '#title' => t('Node ID'),
    '#description' => t('Enter the node ID of the node that should be '.
                        'displayed at this page. Enter 0 to use the '.
                        'first argument as node ID like other node '.
                        'page type does.'),
    '#required' => TRUE,
    '#default_value' => $page->options['nid'],
    '#weight' => 2,
  );
}

function pageroute_page_manage_ui($route, $page, &$form, $type) {
  $form['options']['cancel']['#access'] = FALSE;
  $form['options']['content-type'] = array(
    '#type' => 'select',
    '#title' => t('Content type'),
    '#options' => node_get_types('names'),
    '#required' => TRUE,
    '#default_value' => $page->options['content-type'],
    '#weight' => 2,
  );
  $form['options']['add_button'] = array(
    '#type' => 'textfield',
    '#title' => t('Add button label'),
    '#maxlength' => 64,
    '#default_value' => isset($page->options['add_button']) ? $page->options['add_button'] : t('Add'),
    '#description' => t('The label of the Add button. Leave it empty to hide the button.'),
    '#weight' => 5,
  );
  $form['options']['empty'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Overview with no nodes'),
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,          
    '#weight' => 6,
    '#description' => t('Configure how the page looks like, if there is no node available to list.'),
  );
  $form['options']['empty']['force_add'] = array(
    '#type' => 'radios',
    '#title' => '',
    '#default_value' => $page->options['empty']['force_add'] ? 1 : 0,
    '#options' => array(
      0 => t('Show an add button and a short message that there is no node yet.'),
      1 => t('Show a node add form.'),
    ),
    '#weight' => 0,
  );
  $form['options']['empty']['cancel'] = array(
    '#type' => 'textfield',
    '#title' => t('Cancel link label'),
    '#maxlength' => 64,
    '#default_value' => isset($page->options['empty']['cancel']) ? $page->options['empty']['cancel'] : t('Cancel'),
    '#description' => t('If the node add form has been chosen, the label of the cancel link. Leave it empty to hide the link, but not that this would force the user to add a node.'),
    '#weight' => 4,
  );
  $form['options']['empty']['add_button'] = array(
    '#type' => 'textfield',
    '#title' => t('Add button label'),
    '#maxlength' => 64,
    '#default_value' => isset($page->options['empty']['add_button']) ? $page->options['empty']['add_button'] : t('Add'),
    '#description' => t('If shown, the label of the add button. Leave it empty to hide the button in any case.'),
    '#weight' => 4,
  );
  $groups = array(
    'add' => t('Node add form'),
    'edit' => t('Node edit form')
  );
  foreach ($groups as $name => $title) {
    $form['options'][$name] = array(
      '#type' => 'fieldset', 
      '#title' => $title,
      '#collapsed' => TRUE,
      '#collapsible' => TRUE,          
      '#weight' => 8,
    );
    $form['options'][$name]['forward'] = array(
      '#type' => 'textfield', 
      '#title' => t('Forward button label'),
      '#maxlength' => 32,
      '#default_value' => isset($page->options[$name]['forward']) ? $page->options[$name]['forward'] : t('Forward'),
      '#description' => t('The label of the forward button. Leave it empty to hide the button.'),
      '#weight' => 3,
    );
    $form['options'][$name]['back'] = array(
      '#type' => 'textfield', 
      '#title' => t('Back button label'),
      '#maxlength' => 32,
      '#default_value' => $page->options[$name]['back'],
      '#description' => t('The label of the back button. Leave it empty to hide the button.'),
      '#weight' => 4,
    );
    $form['options'][$name]['cancel'] = array(
      '#type' => 'textfield',
      '#title' => t('Cancel link label'),
      '#maxlength' => 32,
      '#default_value' => isset($page->options[$name]['cancel']) ? $page->options[$name]['cancel'] : t('Cancel'),
      '#description' => t('The label of the cancel link. Leave it empty to hide the link, but note that the link is the only possibility for the user to not save the form but staying in the route.'),
      '#weight' => 4,
    );
    $form['options'][$name]['preview'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display preview button'),
      '#default_value' => $page->options[$name]['preview'],
      '#weight' => 5,        
    );
    $form['options'][$name]['submit'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display submit button'),
      '#default_value' => isset($page->options[$name]['submit']) ? $page->options[$name]['submit'] : 1,
      '#weight' => 5,        
    );
    if ($name != 'add') {
      $form['options'][$name]['nodelete'] = array(
        '#type' => 'checkbox',
        '#title' => t('Never display the delete button'),
        '#default_value' => isset($page->options[$name]['nodelete']) ? $page->options[$name]['nodelete'] : 1,
        '#weight' => 5,        
      );
      $form['options'][$name]['#weight'] = 9;
    }
  }
}

function pageroute_page_user_edit_ui($route, $page, &$form, $type) {
  $categories = array();
  foreach (_user_categories(false) as $category) {
    $categories[$category['name']] = $category['title'];
  }
  $form['options']['category'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#description' => t('The form of the chosen category will be used for this page.'),
    '#required' => TRUE,
    '#default_value' => $page->options['category'],
    '#weight' => 2,
    '#options' => $categories,
  );
}

/*
 * Implementations of hook_page_type_help().
 */
function pageroute_page_add_help() {
  return t('A page of this type will present a common node adding form '.
           'of a configurable content-type. The id of the new node will be '.
           'added as new argument to the current path, so that other pages '.
           'like a node view page can make use of it.');
}

function pageroute_page_edit_help() {
  return t('A page of this type will present a common node editing form '.
           'of a configurable content-type. It will '.
           'edit the node with the id taken from the first argument of '.
           'the pageroute. Furthermore this type can be configured to show a '.
           'node adding form of a specific content-type if the node id argument '.
           'is missing. So you can build a '.
           'pageroute that manages the creation and editing of nodes of '.
           'the same type.');
}

function pageroute_page_manage_help() {
  return t('The node management page allows one to add, edit or delete '.
           'nodes from a configurable content type from inside one page! It shows a themeable '.
           'list of already created nodes of the configured type and allows editing and deleting '.
           'if the user has the appropriate access rights.');
}

function pageroute_page_view_help() {
  return t('This page type just displays a configurable node. It can also '.
           'be configured to display the node with the id taken from the '.
           'first argument. Combined with a node adding or editing form, '.
           'this enables you to build a page that shows the added or updated node.');
}

function pageroute_page_user_edit_help() {
  return t('A page of this type will present users\' account editing page '.
         'inside a pageroute. By giving a user id as second pageroute argument '.
         'it\'s also possible for administrators to edit another users\' account.'. 
         'By choosing another category it could also be used to integrate a drupal user profile into a pageroute.'). '<br />'.
         t('!warn This page type is still experimental. If you consider using it, make '.
         'sure you \'ve read !link before!', 
         array('!warn' => '<strong>'.t('Warning!').'</strong>', '!link' => l(t('this issue'), 'http://drupal.org/node/128045')));
         
}