<?php
// $Id: panels.views.inc,v 1.1.2.3 2009/01/08 04:22:22 michellec Exp $

/**
 * @file
 * Holds the panels views panes export.
 */

/**
 * Implementation of hook_default_panel_views().
 */
function _advanced_profile_default_panel_views() {
  if (module_exists('buddylist')) {
    $panel_view = new stdClass();
      $panel_view->pvid = 'new';
      $panel_view->view = 'buddylist_gallery';
      $panel_view->name = 'buddylist_gallery';
      $panel_view->description = '[APK] Names and avatars of a given user\'s buddies';
      $panel_view->title = 'Buddylist Gallery';
      $panel_view->category = 'Advanced Profile Kit';
      $panel_view->category_weight = '0';
      $panel_view->view_type = 'embed';
      $panel_view->use_pager = '0';
      $panel_view->pager_id = '0';
      $panel_view->nodes_per_page = '8';
      $panel_view->offset = '0';
      $panel_view->link_to_view = '0';
      $panel_view->more_link = '1';
      $panel_view->more_text = 'view all buddies';
      $panel_view->feed_icons = '0';
      $panel_view->url_override = '0';
      $panel_view->url = '';
      $panel_view->url_from_panel = '0';
      $panel_view->contexts = array (
      0 => 
      array (
        'type' => 'context',
        'context' => 'user',
        'panel' => '0',
        'fixed' => '',
        'label' => 'Buddylist: Usernode is buddy of UID',
      ),
    );
      $panel_view->allow_type = NULL;
      $panel_view->allow_nodes_per_page = '1';
      $panel_view->allow_offset = '0';
      $panel_view->allow_use_pager = '1';
      $panel_view->allow_link_to_view = '0';
      $panel_view->allow_more_link = '1';
      $panel_view->allow_more_text = '1';
      $panel_view->allow_feed_icons = '0';
      $panel_view->allow_url_override = '0';
      $panel_view->allow_url_from_panel = '0';
    $panel_views['buddylist_gallery'] = $panel_view;
  }

  $panel_view = new stdClass();
    $panel_view->pvid = 'new';
    $panel_view->view = 'user_tracker';
    $panel_view->name = 'user_tracker';
    $panel_view->description = '[APK] Shows recent posts by a given user';
    $panel_view->title = 'Topics I\'ve participated in';
    $panel_view->category = 'Advanced Profile Kit';
    $panel_view->category_weight = '-1';
    $panel_view->view_type = 'embed';
    $panel_view->use_pager = '0';
    $panel_view->pager_id = '0';
    $panel_view->nodes_per_page = '5';
    $panel_view->offset = '0';
    $panel_view->link_to_view = '0';
    $panel_view->more_link = '1';
    $panel_view->more_text = 'See more posts';
    $panel_view->feed_icons = '0';
    $panel_view->url_override = '0';
    $panel_view->url = '';
    $panel_view->url_from_panel = '0';
    $panel_view->contexts = array (
    0 => 
    array (
      'type' => 'context',
      'context' => 'user',
      'panel' => '0',
      'fixed' => '',
      'label' => 'User: UID is Author',
    ),
  );
    $panel_view->allow_type = NULL;
    $panel_view->allow_nodes_per_page = '1';
    $panel_view->allow_offset = '0';
    $panel_view->allow_use_pager = '0';
    $panel_view->allow_link_to_view = '0';
    $panel_view->allow_more_link = '0';
    $panel_view->allow_more_text = '1';
    $panel_view->allow_feed_icons = '0';
    $panel_view->allow_url_override = '0';
    $panel_view->allow_url_from_panel = '0';
  $panel_views['user_tracker'] = $panel_view;


  return $panel_views;
}
