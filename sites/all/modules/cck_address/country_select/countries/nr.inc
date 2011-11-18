<?php
// $Id: nr.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "Nauru" specific data
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
function addresses_province_list_nr() {
  return array(
    'AO' => t('Aiwo'),
    'AA' => t('Anabar'),
    'AT' => t('Anetan'),
    'AI' => t('Anibare'),
    'BA' => t('Baiti'),
    'BO' => t('Boe'),
    'BU' => t('Buada'),
    'DE' => t('Denigomodu'),
    'EW' => t('Ewa'),
    'IJ' => t('Ijuw'),
    'ME' => t('Meneng'),
    'NI' => t('Nibok'),
    'UA' => t('Uaboe'),
    'YA' => t('Yaren')
  );
}
