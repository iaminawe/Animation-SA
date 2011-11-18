<?php
// $Id: profile.author-pane.inc,v 1.1.4.2 2009/03/05 03:24:53 michellec Exp $

/**
 * @file
 *   Provides a preprocess function on behalf of the profile module.
 */

/**
 * Implementation of hook_preprocess_author_pane().
 */
function profile_preprocess_author_pane(&$variables) {
  $account_id = $variables['account']->uid;
  if ($account_id != 0) {
    $variables['profile'] = profile_view_profile($variables['account']);
  }
}  