<?php
// $Id: views.user-list.inc,v 1.1.2.3 2009/01/08 04:22:22 michellec Exp $

/**
 * @file
 * Holds user list view export.
 */

  $view = new stdClass();
  $view->name = 'user_list';
  $view->description = '[APK] Filterable list of users with profiles';
  $view->access = array (
);
  $view->view_args_php = '';
  $view->page = TRUE;
  $view->page_title = 'User List';
  $view->page_header = '';
  $view->page_header_format = '1';
  $view->page_footer = '';
  $view->page_footer_format = '1';
  $view->page_empty = 'No users match your criteria.';
  $view->page_empty_format = '1';
  $view->page_type = 'list';
  $view->url = 'user-list';
  $view->use_pager = TRUE;
  $view->nodes_per_page = '10';
  $view->menu = TRUE;
  $view->menu_title = 'User Listing';
  $view->menu_tab = FALSE;
  $view->menu_tab_weight = '0';
  $view->menu_tab_default = FALSE;
  $view->menu_tab_default_parent = NULL;
  $view->menu_tab_default_parent_type = 'tab';
  $view->menu_parent_tab_weight = '0';
  $view->menu_parent_title = '';
  $view->sort = array (
  );
  $view->argument = array (
  );
  $view->field = array (
    array (
      'tablename' => 'users',
      'field' => 'uid',
      'label' => '',
    ),
    array (
      'tablename' => 'users',
      'field' => 'name',
      'label' => '',
    ),
    array (
      'tablename' => 'node_data_field_about_me',
      'field' => 'field_about_me_value',
      'label' => '',
      'handler' => 'content_views_field_handler_group',
      'options' => 'default',
    ),
  );
  $view->filter = array (
    array (
      'tablename' => 'node',
      'field' => 'type',
      'operator' => 'OR',
      'options' => '',
      'value' => array (
  0 => 'uprofile',
),
    ),
    array (
      'tablename' => 'node',
      'field' => 'status',
      'operator' => '=',
      'options' => '',
      'value' => '1',
    ),
    array (
      'tablename' => 'node_data_field_gender',
      'field' => 'field_gender_value_default',
      'operator' => 'OR',
      'options' => '',
      'value' => array (
  0 => 'Male',
  1 => 'Female',
  2 => 'Undecided',
),
    ),
    array (
      'tablename' => 'node_data_field_status',
      'field' => 'field_status_value_default',
      'operator' => 'OR',
      'options' => '',
      'value' => array (
  0 => 'Single: not looking',
  1 => 'Single: looking',
  2 => 'In a relationship',
  3 => 'Married',
  4 => 'Divorced',
  5 => 'Widowed',
),
    ),
    array (
      'tablename' => 'node_data_field_children',
      'field' => 'field_children_value_default',
      'operator' => 'OR',
      'options' => '',
      'value' => array (
  0 => 'No children: not planning on having any',
  1 => 'No children: would like some now or in the future',
  2 => 'Have young child(ren)',
  3 => 'Have grown children',
  4 => 'My pets are my kids',
),
    ),
    array (
      'tablename' => 'node_data_field_education',
      'field' => 'field_education_value_default',
      'operator' => 'OR',
      'options' => '',
      'value' => array (
  0 => 'Before high school',
  1 => 'In high school',
  2 => 'Some high school',
  3 => 'Completed high school',
  4 => 'In college',
  5 => 'Some college',
  6 => 'Completed college',
  7 => 'In post graduate',
  8 => 'Some post graduate',
  9 => 'Completed post graduate',
),
    ),
  );
  $view->exposed_filter = array (
    array (
      'tablename' => 'node_data_field_gender',
      'field' => 'field_gender_value_default',
      'label' => 'Gender',
      'optional' => '1',
      'is_default' => '0',
      'operator' => '1',
      'single' => '1',
    ),
    array (
      'tablename' => 'node_data_field_status',
      'field' => 'field_status_value_default',
      'label' => 'Status',
      'optional' => '1',
      'is_default' => '0',
      'operator' => '1',
      'single' => '1',
    ),
    array (
      'tablename' => 'node_data_field_children',
      'field' => 'field_children_value_default',
      'label' => 'Children',
      'optional' => '1',
      'is_default' => '0',
      'operator' => '1',
      'single' => '1',
    ),
    array (
      'tablename' => 'node_data_field_education',
      'field' => 'field_education_value_default',
      'label' => 'Education',
      'optional' => '1',
      'is_default' => '0',
      'operator' => '1',
      'single' => '1',
    ),
  );
  $view->requires = array(users, node_data_field_about_me, node, node_data_field_gender, node_data_field_status, node_data_field_children, node_data_field_education);
  $views[$view->name] = $view;

