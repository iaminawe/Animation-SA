<?php
// $Id: user_badges.author-pane.inc,v 1.1.4.3 2009/03/05 03:24:53 michellec Exp $

/**
 * @file
 *   Provides a preprocess function on behalf of the user badges module.
 */

/**
 * Implementation of hook_preprocess_author_pane().
 */
function user_badges_preprocess_author_pane(&$variables) {
  $account_id = $variables['account']->uid;

  if ($account_id != 0) {
    $variables['user_badges'] = user_badges_for_uid($account_id);
  }
}