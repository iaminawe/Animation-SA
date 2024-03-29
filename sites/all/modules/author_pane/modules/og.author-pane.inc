<?php
// $Id: og.author-pane.inc,v 1.1.4.3 2009/03/05 03:24:53 michellec Exp $

/**
 * @file
 *   This file provides a preprocess function on behalf of the OG module.
 */

/**
 * Implementation of hook_preprocess_author_pane().
 */
function og_preprocess_author_pane(&$variables) {
  $account = $variables['account'];

  if (isset($account->og_groups) && !empty($account->og_groups)) {
    $groups = array();
    foreach ($account->og_groups as $og_id => $og) {
      $groups[] = l($og['title'], 'node/' . $og['nid']);
    }

    $variables['og_groups'] = implode(', ', $groups);
  }
  else {
    $variables['og_groups'] = t('None');
  }
}
