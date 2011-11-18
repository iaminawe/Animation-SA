<?php
// $Id: tv.inc,v 1.1 2009/05/03 03:00:35 newzeal Exp $

/**
 * @file
 * "Tuvalu" specific data
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
function addresses_province_list_tv() {
  return array(
    'NMG' => t('Nanumanga'),
    'NLK' => t('Niulakita'),
    'NTO' => t('Niutao'),
    'FUN' => t('Funafuti'),
    'NME' => t('Nanumea'),
    'NUI' => t('Nui'),
    'NFT' => t('Nukufetau'),
    'NLL' => t('Nukulaelae'),
    'VAI' => t('Vaitupu')
  );
}
