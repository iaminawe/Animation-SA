<?php
// $Id: au.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "Australia" specific data
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
function addresses_province_list_au() {
  return array(
    'ACT' => t('Australian Capital Territory'),
    'NSW' => t('New South Wales'),
    'NT' => t('Northern Territory'),
    'QLD' => t('Queensland'),
    'SA' => t('South Australia'),
    'TAS' => t('Tasmania'),
    'VIC' => t('Victoria'),
    'WA' => t('Western Australia')
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
function addresses_address_format_au() {
  return '!aname
!additional
!street
!city !province_name !postal_code
!country_name';
}
