<?php
// $Id: dj.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "Djibouti" specific data
 */

/**
 * Implementation of hook_province_list().
 *
 * Its a hook from Addresses module to list all
 * states/provinces/teritories of a given country
 *
 * @return
 *   Array. states where the keys are the state
 *   code and the value is the state name
 */
function addresses_province_list_dj() {
  return array(
    'S' => t("'Ali Sabih"),
    'K' => t('Dikhil'),
    'J' => t('Djibouti'),
    'O' => t('Obock'),
    'T' => t('Tadjoura')
  );
}
