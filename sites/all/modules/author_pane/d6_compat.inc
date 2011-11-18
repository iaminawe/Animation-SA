<?php
// $Id: d6_compat.inc,v 1.1.2.3 2009/03/05 03:24:53 michellec Exp $

/*****************************************************************************/
/**************************** Preprocessor ***********************************/
/*****************************************************************************/

/**
 * Call preprocess functions for a theme hook.
 *
 * By calling this in a theme function prior to calling the template callback,
 * we emulate the theme registry and preprocessor hooks of D6.
 * @param $hook
 * A theme hook that need preprocessing.
 * @param $variables
 * The theme variables array. This is used to return by reference.
 * @return
 * Return by reference the $variables array
 */
function author_pane_call_preprocess($hook, &$variables) {
  $functions = author_pane_get_preprocess($hook);
  $args = array(&$variables, $hook);
  foreach ($functions as $function) {
    if (function_exists($function)) {
      call_user_func_array($function, $args);
    }
  }
}

/**
 * Get a list of preprocess functions for a given hook.
 *
 * @param $hook
 * A theme hook that need preprocessing.
 * @return
 * An array or preprocessor function.
 */
function author_pane_get_preprocess($hook) {
  static $registry;

  if (!isset($registry)) {
    global $theme;
    // Check the theme registry cache; if it exists, use it.
    $cache = cache_get("author_pane_registry:$theme", 'cache');
    if (isset($cache->data) && $cache->data) {
      $registry = unserialize($cache->data);
    }
    else {
      // We'll build it below.
      $registry = array();
    }
  }

  // If we don't have registry or don't have an entry, build one and cache it.
  // This will build the registry as needed so unused functions won't be polluting it.
  if (empty($registry) || !isset($registry[$hook])) {
    global $theme;
    $registry[$hook] = _author_pane_build_preprocess($hook);
    cache_set("author_pane_registry:$theme", 'cache', serialize($registry));
  }

  return $registry[$hook];
}

/**
 * Helper function that does the leg work of finding preprocessor functions for a given hook.
 *
 * @param $hook
 * A theme hook that need preprocessing.
 * @return
 * An array of preprocessor functions.
 */
function _author_pane_build_preprocess($hook) {
  $return = array();
  // Default preprocessor prefix.
  $prefixes['template'] = 'template';
  
  // Add all modules so they can intervene with their own preprocessors. This allows them
  // to provide preprocess functions even if they are not the owner of the current hook.
  $prefixes += module_list();

  // Some modules in d5 already have functions that look like preprocess hooks.
  unset($prefixes['search']);

  foreach ($prefixes as $prefix) {
    if (function_exists($prefix .'_preprocess')) {
      $return[] = $prefix .'_preprocess';
    }
    if (function_exists($prefix .'_preprocess_'. $hook)) {
      $return[] = $prefix .'_preprocess_'. $hook;
    }
  }
  return $return;
}

