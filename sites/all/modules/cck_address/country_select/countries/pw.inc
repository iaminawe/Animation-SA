<?php
// $Id: pw.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "Palau" specific data
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
function addresses_province_list_pw() {
  return array(
    'AM' => t('Aimeliik'),
    'AR' => t('Airai'),
    'AN' => t('Angaur'),
    'HA' => t('Hatohobei'),
    'KA' => t('Kayangel'),
    'KO' => t('Koror'),
    'ME' => t('Melekeok'),
    'NA' => t('Ngaraard'),
    'NG' => t('Ngarchelong'),
    'ND' => t('Ngardmau'),
    'NT' => t('Ngatpang'),
    'NC' => t('Ngchesar'),
    'NR' => t('Ngeremlengui'),
    'NW' => t('Ngiwal'),
    'PE' => t('Peleliu'),
    'SO' => t('Sonsorol')
  );
}
