<?php
// $Id: views.user-tracker.inc,v 1.1.2.3 2009/01/08 04:22:22 michellec Exp $

/**
 * @file
 * Holds user tracker view export.
 */

  $view = new stdClass();
  $view->name = 'user_tracker';
  $view->description = '[APK] Shows recent posts a given user authored or commented on';
  $view->access = array (
);
  $view->view_args_php = '';
  $view->page = TRUE;
  $view->page_title = '';
  $view->page_header = '';
  $view->page_header_format = '1';
  $view->page_footer = '';
  $view->page_footer_format = '1';
  $view->page_empty = 'No posts available.';
  $view->page_empty_format = '1';
  $view->page_type = 'table';
  $view->url = 'users/$arg/posts';
  $view->use_pager = TRUE;
  $view->nodes_per_page = '25';
  $view->menu = TRUE;
  $view->menu_title = 'Recent posts';
  $view->menu_tab = FALSE;
  $view->menu_tab_weight = '0';
  $view->menu_tab_default = FALSE;
  $view->menu_tab_default_parent = NULL;
  $view->menu_tab_default_parent_type = 'tab';
  $view->menu_parent_tab_weight = '0';
  $view->menu_parent_title = '';
  $view->block = TRUE;
  $view->block_title = '';
  $view->block_header = '';
  $view->block_header_format = '1';
  $view->block_footer = '';
  $view->block_footer_format = '1';
  $view->block_empty = '';
  $view->block_empty_format = '1';
  $view->block_type = 'list';
  $view->nodes_per_block = '5';
  $view->block_more = TRUE;
  $view->block_use_page_header = FALSE;
  $view->block_use_page_footer = FALSE;
  $view->block_use_page_empty = FALSE;
  $view->sort = array (
    array (
      'tablename' => 'node_comment_statistics',
      'field' => 'last_comment_timestamp',
      'sortorder' => 'DESC',
      'options' => 'normal',
    ),
  );
  $view->argument = array (
    array (
      'type' => 'uidtouch',
      'argdefault' => '7',
      'title' => '',
      'options' => '',
      'wildcard' => '',
      'wildcard_substitution' => '',
    ),
  );
  $view->field = array (
    array (
      'tablename' => 'node',
      'field' => 'type',
      'label' => 'Type',
    ),
    array (
      'tablename' => 'node',
      'field' => 'title',
      'label' => 'Title',
      'handler' => 'views_handler_field_nodelink_with_mark',
      'options' => 'link',
    ),
    array (
      'tablename' => 'node_comment_statistics',
      'field' => 'comment_count',
      'label' => 'Replies',
      'handler' => 'views_handler_comments_with_new',
    ),
    array (
      'tablename' => 'node_comment_statistics',
      'field' => 'last_comment_timestamp',
      'label' => 'Last Post',
      'handler' => 'views_handler_field_since',
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
      'operator' => 'NOR',
      'options' => '',
      'value' => array (
  0 => 'uprofile',
),
    ),
  );
  $view->exposed_filter = array (
  );
  $view->requires = array(node_comment_statistics, node);
  $views[$view->name] = $view;
