<?php
// $Id: views.buddylist-gallery.inc,v 1.1.2.3 2009/01/08 04:22:22 michellec Exp $

/**
 * @file
 * Holds buddylist gallery view export.
 */

  $view = new stdClass();
  $view->name = 'buddylist_gallery';
  $view->description = '[APK] Names and avatars of a given user\'s buddies';
  $view->access = array (
);
  $view->view_args_php = '';
  $view->page = TRUE;
  $view->page_title = 'Buddylist Gallery';
  $view->page_header = '';
  $view->page_header_format = '1';
  $view->page_footer = '';
  $view->page_footer_format = '1';
  $view->page_empty = 'User has no buddies';
  $view->page_empty_format = '1';
  $view->page_type = 'bonus_grid';
  $view->url = 'buddylist_gallery/$arg';
  $view->use_pager = TRUE;
  $view->nodes_per_page = '30';
  $view->sort = array (
    array (
      'tablename' => 'node',
      'field' => 'created',
      'sortorder' => 'DESC',
      'options' => 'normal',
    ),
  );
  $view->argument = array (
    array (
      'type' => 'buddylist_buddies',
      'argdefault' => '7',
      'title' => '',
      'options' => '',
      'wildcard' => '',
      'wildcard_substitution' => '',
    ),
  );
  $view->field = array (
    array (
      'tablename' => 'users',
      'field' => 'uid',
      'label' => '',
    ),
    array (
      'tablename' => 'usernode_users',
      'field' => 'name',
      'label' => '',
      'handler' => 'usernode_views_handler_field_username_link',
    ),
  );
  $view->filter = array (
    array (
      'tablename' => 'node',
      'field' => 'status',
      'operator' => '=',
      'options' => '',
      'value' => '1',
    ),
    array (
      'tablename' => 'node',
      'field' => 'type',
      'operator' => 'OR',
      'options' => '',
      'value' => array (
  0 => 'usernode',
),
    ),
  );
  $view->exposed_filter = array (
  );
  $view->requires = array(node, users, usernode_users);
  $views[$view->name] = $view;
