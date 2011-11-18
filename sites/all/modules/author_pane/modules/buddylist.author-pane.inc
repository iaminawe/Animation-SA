<?php
// $Id: buddylist.author-pane.inc,v 1.1.2.2 2009/03/05 03:24:53 michellec Exp $

/**
 * @file
 *   Provides a preprocess function on behalf of the buddylist module.
 */

/**
 * Implementation of hook_preprocess_author_pane().
 */
function buddylist_preprocess_author_pane(&$variables) {
  global $user;
  $account_id = $variables['account']->uid;
  $image_path = $variables['image_path'];
  
  if ($account_id != 0 && user_access('maintain buddy list') && $user->uid != $account_id) {
   
    if (@in_array($account_id, array_keys(buddylist_get_buddies($user->uid)))) {
      // Remove buddy
      $variables['buddylist'] =   
        l(theme('image', "$image_path/buddy-remove.png", 
                t('Remove from buddylist'), t('Remove from buddylist'), NULL, TRUE), 
          "buddy/delete/$account_id",
          array(), NULL, NULL, FALSE, TRUE); 
      
      $variables['buddylist_link'] = l("Remove buddy", "buddy/delete/$account_id");
    } 
    else {
      // Add buddy
      $variables['buddylist'] =   
        l(theme('image', "$image_path/buddy-add.png", 
                t('Add to buddylist'), t('Add to buddylist'), NULL, TRUE), 
          "buddy/add/$account_id",
          array(), NULL, NULL, FALSE, TRUE); 
      
      $variables['buddylist_link'] = l("Add buddy", "buddy/add/$account_id");
    }
  }
}