<?php
// $Id: panels.pages.inc,v 1.1.2.4 2009/01/11 05:20:44 michellec Exp $

/**
 * @file
 * Holds the panels pages export.
 */

/**
 * Implementation of hook_default_panel_pages()
 */
function _advanced_profile_default_panel_pages() {
  $page = new stdClass();
  $page->pid = 'new';
    $page->name = 'user_profile';
    $page->title = 'User profile';
    $page->arguments = array (
    0 => 
    array (
      'name' => 'uid',
      'default' => '404',
      'title' => '%user',
      'id' => 1,
      'identifier' => 'User ID',
      'keyword' => 'user',
      'argument_settings' => NULL,
    ),
  );
    $page->relationships = array (
    0 => 
    array (
      'context' => 'argument_uid_1',
      'name' => 'node_from_user',
      'id' => 1,
      'identifier' => 'User uprofile',
      'keyword' => 'node',
    ),
  );
    $page->access = array();
    $page->path = 'user/%';
    $page->css_id = 'user-profile';
    $page->no_blocks = '0';
    $page->switcher_options = array();
    $page->menu = '0';
  $page->contexts = array();
  $display = new panels_display();
  $display->did = 'new';
  $display->layout = 'flexible';
  $display->layout_settings = array (
    'width_type' => '%',
    'percent_width' => '100',
    'rows' => '2',
    'row_1' => 
    array (
      'columns' => '2',
      'width_1' => '30',
      'width_2' => '70',
      'names' => 
      array (
        0 => 'Left',
        1 => 'Right',
      ),
    ),
    'row_2' => 
    array (
      'columns' => '1',
      'width_1' => '100',
      'names' => 
      array (
        0 => 'Bottom',
      ),
    ),
    'sidebars' => 
    array (
      'left' => 0,
      'left_width' => 200,
      'right' => 0,
      'right_width' => 200,
      'width_type' => 'px',
    ),
  );
  $display->panel_settings = array (
    'style' => 'rounded_corners',
    'style_settings' => 
    array (
    ),
    'edit_style' => 'Edit style settings',
    'individual' => 0,
    'panel' => 
    array (
      'row_1_1' => 
      array (
        'style' => '',
        'edit_style' => 'Edit style settings',
      ),
      'row_1_2' => 
      array (
        'style' => '',
        'edit_style' => 'Edit style settings',
      ),
      'row_2_1' => 
      array (
        'style' => '',
        'edit_style' => 'Edit style settings',
      ),
    ),
    'did' => '5',
  );
  $display->cache = array();
  $display->title = '';
  $display->hide_title = '0';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
      $pane->pid = 'new-1';
      $pane->panel = 'row_1_1';
      $pane->type = 'author_pane';
      $pane->subtype = 'description';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 'argument_uid_1',
        'style' => 'default',
        'override_title' => 1,
        'override_title_text' => '%user',
        'css_id' => 'profile-author-pane',
        'css_class' => '',
        'image_path' => '',
        'template_file' => 'advanced_profile_author-pane',
      );
      $pane->cache = array();
    $display->content['new-1'] = $pane;
    $display->panels['row_1_1'][0] = 'new-1';
    $pane = new stdClass();
      $pane->pid = 'new-2';
      $pane->panel = 'row_1_1';
      $pane->type = 'content_fieldgroup';
      $pane->subtype = 'description';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 'relationship_node_from_user_1',
        'style' => 'default',
        'override_title' => 1,
        'override_title_text' => 'Contact',
        'css_id' => 'profile-contact',
        'css_class' => '',
        'type_name' => 'uprofile',
        'group' => 'group_contact',
        'empty' => '',
      );
      $pane->cache = array();
    $display->content['new-2'] = $pane;
    $display->panels['row_1_1'][1] = 'new-2';
    $pane = new stdClass();
      $pane->pid = 'new-3';
      $pane->panel = 'row_1_1';
      $pane->type = 'content_fieldgroup';
      $pane->subtype = 'description';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 'relationship_node_from_user_1',
        'style' => 'default',
        'override_title' => 1,
        'override_title_text' => 'Stats',
        'css_id' => 'profile-stats',
        'css_class' => '',
        'type_name' => 'uprofile',
        'group' => 'group_stats',
        'empty' => '',
      );
      $pane->cache = array();
    $display->content['new-3'] = $pane;
    $display->panels['row_1_1'][2] = 'new-3';
    $pane = new stdClass();
      $pane->pid = 'new-4';
      $pane->panel = 'row_1_1';
      $pane->type = 'content_fieldgroup';
      $pane->subtype = 'description';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 'relationship_node_from_user_1',
        'style' => 'default',
        'override_title' => 1,
        'override_title_text' => 'Links',
        'css_id' => 'profile-links',
        'css_class' => '',
        'type_name' => 'uprofile',
        'group' => 'group_links',
        'empty' => '',
      );
      $pane->cache = array();
    $display->content['new-4'] = $pane;
    $display->panels['row_1_1'][3] = 'new-4';
    $pane = new stdClass();
      $pane->pid = 'new-5';
      $pane->panel = 'row_1_1';
      $pane->type = 'profile_visitors';
      $pane->subtype = 'description';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 'argument_uid_1',
        'style' => 'default',
        'override_title' => 0,
        'override_title_text' => '',
        'css_id' => 'profile-visitors',
        'css_class' => '',
      );
      $pane->cache = array();
    $display->content['new-5'] = $pane;
    $display->panels['row_1_1'][4] = 'new-5';
    $pane = new stdClass();
      $pane->pid = 'new-6';
      $pane->panel = 'row_1_2';
      $pane->type = 'content_field';
      $pane->subtype = 'description';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 'relationship_node_from_user_1',
        'style' => 'default',
        'override_title' => 1,
        'override_title_text' => 'About',
        'css_id' => 'profile-about',
        'css_class' => '',
        'label' => 'normal',
        'field_formatter' => 'field_about_me:default',
      );
      $pane->cache = array();
    $display->content['new-6'] = $pane;
    $display->panels['row_1_2'][0] = 'new-6';
    $pane = new stdClass();
      $pane->pid = 'new-7';
      $pane->panel = 'row_1_2';
      $pane->type = 'views2';
      $pane->subtype = 'user_tracker';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 
        array (
          0 => 'argument_uid_1',
        ),
        'style' => 'default',
        'override_title' => 1,
        'override_title_text' => 'Topics I\'ve participated in:',
        'css_id' => 'profile-topics',
        'css_class' => '',
        'title' => 'Topics I\'ve participated in',
        'name' => 'user_tracker',
        'nodes_per_page' => '5',
      );
      $pane->cache = array();
    $display->content['new-7'] = $pane;
    $display->panels['row_1_2'][1] = 'new-7';
    $pane = new stdClass();
      $pane->pid = 'new-8';
      $pane->panel = 'row_1_2';
      $pane->type = 'views2';
      $pane->subtype = 'buddylist_gallery';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 
        array (
          0 => 'argument_uid_1',
        ),
        'style' => 'default',
        'override_title' => 0,
        'override_title_text' => '',
        'css_id' => 'profile-friends',
        'css_class' => '',
        'title' => 'Buddylist Gallery',
        'name' => 'buddylist_gallery',
        'more_link' => 1,
        'more_text' => 'view all buddies',
        'use_pager' => 0,
        'pager_id' => '0',
        'nodes_per_page' => '8',
      );
      $pane->cache = array();
    $display->content['new-8'] = $pane;
    $display->panels['row_1_2'][2] = 'new-8';
    $pane = new stdClass();
      $pane->pid = 'new-9';
      $pane->panel = 'row_2_1';
      $pane->type = 'node_comments';
      $pane->subtype = 'comments';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 'relationship_node_from_user_1',
        'style' => 'default',
        'override_title' => 1,
        'override_title_text' => 'Comment wall',
        'css_id' => 'profile-comments',
        'css_class' => '',
        'mode' => '2',
        'order' => '1',
        'comments_per_page' => '10',
      );
      $pane->cache = array();
    $display->content['new-9'] = $pane;
    $display->panels['row_2_1'][0] = 'new-9';
    $pane = new stdClass();
      $pane->pid = 'new-10';
      $pane->panel = 'row_2_1';
      $pane->type = 'node_comment_form';
      $pane->subtype = 'comment_form';
      $pane->shown = '1';
      $pane->access = array();
      $pane->visibility = '';
      $pane->configuration = array (
        'context' => 'relationship_node_from_user_1',
        'style' => 'default',
        'override_title' => 1,
        'override_title_text' => 'Leave a message for %user',
        'css_id' => 'profile-comment-form',
        'css_class' => '',
      );
      $pane->cache = array();
    $display->content['new-10'] = $pane;
    $display->panels['row_2_1'][1] = 'new-10';
  $page->display = $display;
  $page->displays = array();
  $pages['user_profile'] = $page;


  return $pages;
}


