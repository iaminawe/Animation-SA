<?php
// $Id: views.inc,v 1.1.2.3 2009/01/08 04:22:22 michellec Exp $

/**
 * @file
 * Handles integration with the views module.
 */

/**
 * Loads the included views
 */
function advanced_profile_views_default_views() {

  $views_dir = drupal_get_path('module', 'advanced_profile') . '/includes/views/';
  $views = array();

  include_once $views_dir . 'views.user-tracker.inc';
  include_once $views_dir . 'views.user-list.inc';

  if (module_exists("buddylist")) {
    include_once $views_dir . 'views.buddylist-gallery.inc';
  }

  return $views;
}
