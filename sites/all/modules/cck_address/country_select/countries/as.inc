<?php
// $Id: as.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "American Samoa" specific data
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
function addresses_province_list_as() {
  return array(
    'E' => t('Eastern'),
    'M' => t("Manu'a"),
    'R' => t('Rose Island'),
    'S' => t('Swains Island'),
    'W' => t('Western')
  );
}
