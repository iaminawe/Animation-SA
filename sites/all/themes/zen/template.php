<?php
// $Id: template.php,v 1.12.2.57 2008/04/21 10:42:35 johnalbin Exp $

/**
 * @file
 * File which contains theme overrides for the Zen theme.
 *
 * ABOUT
 *
 * The template.php file is one of the most useful files when creating or
 * modifying Drupal themes. You can add new regions for block content, modify or
 * override Drupal's theme functions, intercept or make additional variables
 * available to your theme, and create custom PHP logic. For more information,
 * please visit the Theme Developer's Guide on Drupal.org:
 * http://drupal.org/theme-guide
 *
 * NOTE ABOUT ZEN'S TEMPLATE.PHP FILE
 *
 * The base Zen theme is designed to be easily extended by its sub-themes. You
 * shouldn't modify this or any of the CSS or PHP files in the root zen/ folder.
 * See the online documentation for more information:
 *   http://drupal.org/node/193318
 */


/*
 * To make this file easier to read, we split up the code into managable parts.
 * Theme developers are likely to only be interested in functions that are in
 * this main template.php file.
 */

// Sub-theme support
include_once 'template-subtheme.php';

// Initialize theme settings
include_once 'theme-settings-init.php';

// Tabs and menu functions
include_once 'template-menus.php';


/**
 * Declare the available regions implemented by this theme.
 *
 * Regions are areas in your theme where you can place blocks. The default
 * regions used in themes are "left sidebar", "right sidebar", "header", and
 * "footer", although you can create as many regions as you want. Once declared,
 * they are made available to the page.tpl.php file as a variable. For instance,
 * use <?php print $header ?> for the placement of the "header" region in
 * page.tpl.php.
 *
 * By going to the administer > site building > blocks page you can choose
 * which regions various blocks should be placed. New regions you define here
 * will automatically show up in the drop-down list by their human readable name.
 *
 * @return
 *   An array of regions. The first array element will be used as the default
 *   region for themes. Each array element takes the format:
 *   variable_name => t('human readable name')
 */
function zen_regions() {
  // Allow a sub-theme to define its own regions.
  global $theme_key;
  if ($theme_key != 'zen') {
    $function = str_replace('-', '_', $theme_key) .'_regions';
    if (function_exists($function)) {
      return $function();
    }
  }

  return array(
    'left' => t('left sidebar'),
    'right' => t('right sidebar'),
    'navbar' => t('navigation bar'),
    'content_top' => t('content top'),
    'content_bottom' => t('content bottom'),
    'header' => t('header'),
     'header_login' => t('header_login'),
    'footer' => t('footer'),
    'closure_region' => t('closure'),
  );
}


/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function phptemplate_breadcrumb($breadcrumb) {
  $show_breadcrumb = theme_get_setting('zen_breadcrumb');
  $show_breadcrumb_home = theme_get_setting('zen_breadcrumb_home');
  $breadcrumb_separator = theme_get_setting('zen_breadcrumb_separator');
  $trailing_separator = theme_get_setting('zen_breadcrumb_trailing') ? $breadcrumb_separator : '';

  // Determine if we are to display the breadcrumb
  if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {
    if (!$show_breadcrumb_home) {
      // Optionally get rid of the homepage link
      array_shift($breadcrumb);
    }
    if (!empty($breadcrumb)) {
      // Return the breadcrumb with separators
      return '<div class="breadcrumb">'. implode($breadcrumb_separator, $breadcrumb) ."$trailing_separator</div>";
    }
  }
  // Otherwise, return an empty string
  return '';
}


/*
 * CREATE OR MODIFY VARIABLES FOR YOUR THEME
 *
 * The most powerful function available to themers is _phptemplate_variables().
 * It allows you to pass newly created variables to different template (tpl.php)
 * files in your theme. Or even unset ones you don't want to use.
 *
 * It works by switching on the hook, or name of the theme function, such as:
 *   - page
 *   - node
 *   - comment
 *   - block
 *
 * By switching on this hook you can send different variables to page.tpl.php
 * file, node.tpl.php (and any other derivative node template file, like
 * node-forum.tpl.php), comment.tpl.php, and block.tpl.php.
 */


/**
 * Intercept template variables
 *
 * @param $hook
 *   The name of the theme function being called (name of the .tpl.php file.)
 * @param $vars
 *   A copy of the array containing the variables for the hook.
 * @return
 *   The array containing additional variables to merge with $vars.
 */
 
function _phptemplate_variables($hook, $vars = array()) {
  if (module_exists('advanced_profile')) {
    $vars = advanced_profile_addvars($hook, $vars);
  }
    if (module_exists('advanced_forum')) {
    $vars = advanced_forum_addvars($hook, $vars);
    }
    /** 
     $current_panel = panels_page_get_current();
  if (!isset($current_panel->pid)) {
    // Load our default panel, call it by name.
    $panel = panels_page_view_page('DEFAULT', false);
    // Insert the actual content of the page using string replace.
    $panel = str_replace('%CONTENT%', $vars['content'], $panel);
    // Replace the page content with our altered panel.
    $vars['content'] = $panel;
  }
 
  */
  global $theme_key;

  // Allow modules to add or alter variables.
  // This construct ensures that we can keep a reference through
  // call_user_func_array.
  $args = array(&$vars, $hook);
  foreach (module_implements('preprocess') as $module) {
    if ($module != 'search') { // Don't call search_preprocess().
      $function = $module .'_preprocess';
      call_user_func_array($function, $args);
    }
  }
  foreach (module_implements('preprocess_'. $hook) as $module) {
    $function = $module .'_preprocess_'. $hook;
    call_user_func_array($function, $args);
  }

  // Allow the Zen base theme to add or alter variables.
  zen_preprocess($vars, $hook);
  $function = 'zen_preprocess_'. $hook;
  if (function_exists($function)) {
    $function($vars, $hook);
  }

  // Allow a sub-theme to add or alter variables.
  $function = $theme_key .'_preprocess';
  if (function_exists($function)) {
    $function($vars, $hook);
  }
  else {
    $function = 'phptemplate_preprocess';
    if (function_exists($function)) {
      $function($vars, $hook);
    }
  }
  $function = $theme_key .'_preprocess_'. $hook;
  if (function_exists($function)) {
    $function($vars, $hook);
  }
  else {
    $function = 'phptemplate_preprocess_'. $hook;
    if (function_exists($function)) {
      $function($vars, $hook);
    }
  }

  // The following is a deprecated function included for backwards compatibility
  // with Zen 5.x-0.8 and earlier. New sub-themes should not use this function.
  if (function_exists('zen_variables')) {
    $vars = zen_variables($hook, $vars);
  }

  _zen_hook($hook); // Add support for sub-theme template files.

  return $vars;
}


/**
 * Override or insert PHPTemplate variables into all templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called (name of the .tpl.php file.)
 */
function zen_preprocess(&$vars, $hook) {
  // Get the currently logged in user
  global $user;

  // Set a new $is_admin variable. This is determined by looking at the
  // currently logged in user and seeing if they are in the role 'admin'. The
  // 'admin' role will need to have been created manually for this to work this
  // variable is available to all templates.
  $vars['is_admin'] = in_array('admin', $user->roles);

  // Send a new variable, $logged_in, to tell us if the current user is
  // logged in or out. An anonymous user has a user id of 0.
  $vars['logged_in'] = ($user->uid > 0) ? TRUE : FALSE;
}

/**
 * Override or insert PHPTemplate variables into the page templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 */
function zen_preprocess_page(&$vars) {
  global $theme, $theme_key;

  // These next lines add additional CSS files and redefine
  // the $css and $styles variables available to your page template
  if ($theme == $theme_key) { // If we're in the main theme
    // Load the stylesheet for a liquid layout
    if (theme_get_setting('zen_layout') == 'border-politics-liquid') {
      drupal_add_css($vars['directory'] .'/layout-liquid.css', 'theme', 'all');
    }
    // Or load the stylesheet for a fixed width layout
    else {
      drupal_add_css($vars['directory'] .'/layout-fixed.css', 'theme', 'all');
    }
    drupal_add_css($vars['directory'] .'/html-elements.css', 'theme', 'all');
    drupal_add_css($vars['directory'] .'/tabs.css', 'theme', 'all');
    drupal_add_css($vars['directory'] .'/zen.css', 'theme', 'all');
    // Avoid IE5 bug that always loads @import print stylesheets
    $vars['head'] = zen_add_print_css($vars['directory'] .'/print.css');
  }
  // Optionally add the block editing styles.
  if (theme_get_setting('zen_block_editing')) {
    drupal_add_css($vars['directory'] .'/block-editing.css', 'theme', 'all');
  }
  // Optionally add the wireframes style.
  if (theme_get_setting('zen_wireframes')) {
    drupal_add_css($vars['directory'] .'/wireframes.css', 'theme', 'all');
  }
  $vars['css'] = drupal_add_css();
  $vars['styles'] = drupal_get_css();

  // Allow sub-themes to have an ie.css file
  $vars['subtheme_directory'] = path_to_subtheme();

  // Don't display empty help from node_help().
  if ($vars['help'] == "<div class=\"help\"><p></p>\n</div>") {
    $vars['help'] = '';
  }

  // Classes for body element. Allows advanced theming based on context
  // (home page, node of certain type, etc.)
  $body_classes = array();
  $body_classes[] = ($vars['is_front']) ? 'front' : 'not-front';
  $body_classes[] = ($vars['logged_in']) ? 'logged-in' : 'not-logged-in';
  if ($vars['node']->type) {
    // If on an individual node page, put the node type in the body classes
    $body_classes[] = 'node-type-'. $vars['node']->type;
  }
  if ($vars['sidebar_left'] && $vars['sidebar_right']) {
    $body_classes[] = 'two-sidebars';
  }
  elseif ($vars['sidebar_left']) {
    $body_classes[] = 'one-sidebar sidebar-left';
  }
  elseif ($vars['sidebar_right']) {
    $body_classes[] = 'one-sidebar sidebar-right';
  }
  else {
    $body_classes[] = 'no-sidebars';
  }
  if (!$vars['is_front']) {
    // Add unique classes for each page and website section
    $path = drupal_get_path_alias($_GET['q']);
    list($section,) = explode('/', $path, 2);
    $body_classes[] = zen_id_safe('page-'. $path);
    $body_classes[] = zen_id_safe('section-'. $section);
    if (arg(0) == 'node') {
      if (arg(1) == 'add') {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-add'; // Add 'section-node-add'
      }
      elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-'. arg(2); // Add 'section-node-edit' or 'section-node-delete'
      }
    }
  }
  $vars['body_classes'] = implode(' ', $body_classes); // Concatenate with spaces
}

/**
 * Override or insert PHPTemplate variables into the node templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 */
function zen_preprocess_node(&$vars) {
  global $user;

  // Special classes for nodes
  $node_classes = array();
  if ($vars['sticky']) {
    $node_classes[] = 'sticky';
  }
  if (!$vars['node']->status) {
    $node_classes[] = 'node-unpublished';
    $vars['unpublished'] = TRUE;
  }
  else {
    $vars['unpublished'] = FALSE;
  }
  if ($vars['node']->uid && $vars['node']->uid == $user->uid) {
    // Node is authored by current user
    $node_classes[] = 'node-mine';
  }
  if ($vars['teaser']) {
    // Node is displayed as teaser
    $node_classes[] = 'node-teaser';
  }
  // Class for node type: "node-type-page", "node-type-story", "node-type-my-custom-type", etc.
  $node_classes[] = 'node-type-'. $vars['node']->type;
  $vars['node_classes'] = implode(' ', $node_classes); // Concatenate with spaces
}

/**
 * Override or insert PHPTemplate variables into the comment templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 */
function zen_preprocess_comment(&$vars) {
  global $user;

  // We load the node object that the current comment is attached to
  $node = node_load($vars['comment']->nid);
  // If the author of this comment is equal to the author of the node, we
  // set a variable so we can theme this comment uniquely.
  $vars['author_comment'] = $vars['comment']->uid == $node->uid ? TRUE : FALSE;

  $comment_classes = array();

  // Odd/even handling
  static $comment_odd = TRUE;
  $comment_classes[] = $comment_odd ? 'odd' : 'even';
  $comment_odd = !$comment_odd;

  if ($vars['comment']->status == COMMENT_NOT_PUBLISHED) {
    $comment_classes[] = 'comment-unpublished';
    $vars['unpublished'] = TRUE;
  }
  else {
    $vars['unpublished'] = FALSE;
  }
  if ($vars['author_comment']) {
    // Comment is by the node author
    $comment_classes[] = 'comment-by-author';
  }
  if ($vars['comment']->uid == 0) {
    // Comment is by an anonymous user
    $comment_classes[] = 'comment-by-anon';
  }
  if ($user->uid && $vars['comment']->uid == $user->uid) {
    // Comment was posted by current user
    $comment_classes[] = 'comment-mine';
  }
  $vars['comment_classes'] = implode(' ', $comment_classes);

  // If comment subjects are disabled, don't display 'em
  if (variable_get('comment_subject_field', 1) == 0) {
    $vars['title'] = '';
  }
}

/**
 * Override or insert PHPTemplate variables into the block templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 */
function zen_preprocess_block(&$vars) {
  $block = $vars['block'];

  // Special classes for blocks
  $block_classes = array();
  $block_classes[] = 'block-'. $block->module;
  $block_classes[] = 'region-'. $vars['block_zebra'];
  $block_classes[] = $vars['zebra'];
  $block_classes[] = 'region-count-'. $vars['block_id'];
  $block_classes[] = 'count-'. $vars['id'];
  $vars['block_classes'] = implode(' ', $block_classes);

  $vars['edit_links'] = '';
  if (theme_get_setting('zen_block_editing') && user_access('administer blocks')) {
    // Display 'edit block' for custom blocks
    if ($block->module == 'block') {
      $edit_links[] = l('<span>'. t('edit block') .'</span>', 'admin/build/block/configure/'. $block->module .'/'. $block->delta, array('title' => t('edit the content of this block'), 'class' => 'block-edit'), drupal_get_destination(), NULL, FALSE, TRUE);
    }
    // Display 'configure' for other blocks
    else {
      $edit_links[] = l('<span>'. t('configure') .'</span>', 'admin/build/block/configure/'. $block->module .'/'. $block->delta, array('title' => t('configure this block'), 'class' => 'block-config'), drupal_get_destination(), NULL, FALSE, TRUE);
    }

    // Display 'administer views' for views blocks
    if ($block->module == 'views' && user_access('administer views')) {
      $edit_links[] = l('<span>'. t('edit view') .'</span>', 'admin/build/views/'. $block->delta .'/edit', array('title' => t('edit the view that defines this block'), 'class' => 'block-edit-view'), drupal_get_destination(), 'edit-block', FALSE, TRUE);
    }
    // Display 'edit menu' for menu blocks
    elseif (($block->module == 'menu' || ($block->module == 'user' && $block->delta == 1)) && user_access('administer menu')) {
      $edit_links[] = l('<span>'. t('edit menu') .'</span>', 'admin/build/menu', array('title' => t('edit the menu that defines this block'), 'class' => 'block-edit-menu'), drupal_get_destination(), NULL, FALSE, TRUE);
    }
    $vars['edit_links_array'] = $edit_links;
    $vars['edit_links'] = '<div class="edit">'. implode(' ', $edit_links) .'</div>';
  }
}

/**
 * Converts a string to a suitable html ID attribute.
 *
 * - Preceeds initial numeric with 'n' character.
 * - Replaces any character except A-Z, numbers, and underscores with dashes.
 * - Converts entire string to lowercase.
 * - Works for classes too!
 *
 * @param $string
 *   The string
 * @return
 *   The converted string
 */
function zen_id_safe($string) {
  if (is_numeric($string{0})) {
    // If the first character is numeric, add 'n' in front
    $string = 'n'. $string;
  }
  return strtolower(preg_replace('/[^a-zA-Z0-9_-]+/', '-', $string));
}

/**
 * Adds a print stylesheet to the page's $head variable.
 *
 * This is a work-around for a serious bug in IE5 in which it loads print
 * stylesheets for screen display when using an @import method, Drupal's default
 * method when using drupal_add_css().
 *
 * @param $url
 *   The URL of the print stylesheet
 * @return
 *   All the rendered links for the $head variable
 */
function zen_add_print_css($url) {
  global $base_path;
  return drupal_set_html_head(
    '<link'.
    drupal_attributes(
      array(
        'rel' => 'stylesheet',
        'href' => $base_path . $url,
        'type' => 'text/css',
        'media' => 'print',
      )
    ) ." />\n"
  );
}

drupal_add_js('sites/all/scripts/jquery.curvycorners.packed.js');

drupal_add_js(
    '$(document).ready(function() {
      $("div.blockwrap").corner("round 10px");
    });',
    'inline'
  );