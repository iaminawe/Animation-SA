<?php
// $Id: gq.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "Equatorial Guinea" specific data
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
function addresses_province_list_gq() {
  return array(
    'AN' => t('Provincia Annobon'),
    'BN' => t('Provincia Bioko Norte'),
    'BS' => t('Provincia Bioko Sur'),
    'CS' => t('Provincia Centro Sur'),
    'KN' => t('Provincia Kie-Ntem'),
    'LI' => t('Provincia Litoral'),
    'WN' => t('Provincia Wele-Nzas')
  );
}
