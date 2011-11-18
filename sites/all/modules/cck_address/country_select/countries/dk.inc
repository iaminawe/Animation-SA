<?php
// $Id: dk.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "Denmark" specific data
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
function addresses_province_list_dk() {
  return array(
    'CC' => t('Copenhagen (municipality)'),
    'FC' => t('Frederiksberg (municipality)'),
    'CO' => t('Copenhagen'),
    'FR' => t('Frederiksborg'),
    'RO' => t('Roskilde'),
    'WZ' => t('West Zealand'),
    'ST' => t('Storstrom'),
    'FU' => t('Funen'),
    'SJ' => t('South Jutland'),
    'RB' => t('Ribe'),
    'VK' => t('Vejle'),
    'RK' => t('Ringkjobing'),
    'VB' => t('Viborg'),
    'NJ' => t('North Jutland'),
    'AR' => t('Arhus'),
    'BH' => t('Bornholm'),
    'GL' => t('Greenland'),
    'FO' => t('Faroe Islands')
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
function addresses_address_format_dk() {
  return '!aname
!additional
!street
!postal_code !city
!country_name';
}
