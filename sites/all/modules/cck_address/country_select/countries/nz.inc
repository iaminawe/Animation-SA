<?php
// $Id: nz.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "New Zealand" specific data
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
function addresses_province_list_nz() {
  return array(
    'AUK' => t('Auckland'),
    'BOP' => t('Bay of Plenty'),
    'CAN' => t('Canterbury'),
    'GIS' => t('Gisborne'),
    'HKB' => t("Hawke's Bay"),
    'MBH' => t('Marlborough'),
    'MWT' => t('Manawatu-Wanganui'),
    'NSN' => t('Nelson'),
    'NTL' => t('Northland'),
    'OTA' => t('Otago'),
    'STL' => t('Southland'),
    'TAS' => t('Tasman'),
    'TKI' => t('Taranaki'),
    'WGN' => t('Wellington'),
    'WKO' => t('Waikato'),
    'WTC' => t('West Coast')
  );
}

/**
 * Implementation of hook_address_format().
 *
 * Format the address using local preferences. It uses
 * Token module to convert this tokens to their real values.
 *
 * @return
 *   String. The address field tokens
 */
function addresses_address_format_nz() {
  return '!aname
!additional
!street
!city !postal_code
!country_name';
}
