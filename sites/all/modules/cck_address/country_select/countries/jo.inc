<?php
// $Id: jo.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "Jordan" specific data
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
function addresses_province_list_jo() {
  return array(
    'AJ' => t('Ajlun'),
    'AQ' => t("Al 'Aqabah"),
    'BA' => t("Al Balqa'"),
    'KA' => t('Al Karak'),
    'MF' => t('Al Mafraq'),
    'AM' => t("'Amman"),
    'TA' => t('At Tafilah'),
    'ZA' => t("Az Zarqa'"),
    'IR' => t('Irbid'),
    'JA' => t('Jarash'),
    'MN' => t("Ma'an"),
    'MD' => t('Madaba')
  );
}
