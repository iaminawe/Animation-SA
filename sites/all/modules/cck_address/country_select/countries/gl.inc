<?php
// $Id: gl.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "Greenland" specific data
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
function addresses_province_list_gl() {
  return array(
    'A' => t('Avannaa'),
    'T' => t('Tunu'),
    'K' => t('Kitaa')
  );
}
