<?php

// $Id: simplenews_template_settings.inc,v 1.1.2.2 2009/02/11 18:54:45 tbarregren Exp $


/**
 * @file
 * Private implementations of the Simplenews Template module. Don't call these
 * functions. They are subject to changes.
 */


/*****************************************************************************
 * ALTER SIMPLENEWS SETTINGS FORM
 *****************************************************************************/

/**
 * Add Simplenews Template settings to the node type forms.
 */
function _simplenews_template_form_alter_newsletter_settings(&$form, $tid) {
  $form['simplenews_template']['#weight'] = -10;
  _simplenews_template_form_alter_header($form, $tid);
  _simplenews_template_form_alter_footer($form, $tid);
  _simplenews_template_form_alter_style($form, $tid);
}

function _simplenews_template_form_alter_header(&$form, $tid) {

  // Header fieldset.
  $form['simplenews_template']['simplenews_template_header'] = array(
    '#type' => 'fieldset',
    '#title' => t('Header'),
    '#description' => t('The header common for all issues of this newsletter.'),
    '#collapsible' => true,
    '#collapsed' => true,
  );

  // Header in node?
  $form['simplenews_template']['simplenews_template_header']["simplenews_template_header_node_$tid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Include header in nodes?'),
    '#description' => t('Check to include the header when viewing nodes with issues of the newsletter. The header is always included in e-mails with issues of the newsletter.'),
    '#default_value' => simplenews_template_header_node($tid),
  );

  // Header.
  $form['simplenews_template']['simplenews_template_header']["simplenews_template_header_$tid"] = array(
    '#type' => 'textarea',
    '#title' => t('Header'),
    '#description' => t('Enter the content of the newsletter\'s header. Available variables are:') . ' %site ' . t('(the name of your website),') . ' %uri ' . t('(a link to your homepage),') . ' %uri_brief ' . t('(homepage link without the http://),') . ' %mymail ' . t('(your e-mail address),') . ' %date ' . t('(today\'s date),') . ' %login_uri ' . t('(link to login page).'),
    '#default_value' => simplenews_template_header($tid),
  );

  // Header input format.
  $form['simplenews_template']['simplenews_template_header']['simplenews_template_header_format_$tid'] = filter_form(simplenews_template_header_format($tid), 1, array("simplenews_template_header_format_$tid"));

}

function _simplenews_template_form_alter_footer(&$form, $tid) {

  // Footer fieldset.
  $form['simplenews_template']['simplenews_template_footer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Footer'),
    '#description' => t('The footer common for all issues of this newsletter.'),
    '#collapsible' => true,
    '#collapsed' => true,
    );

  // Footer in node?
  $form['simplenews_template']['simplenews_template_footer']["simplenews_template_footer_node_$tid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Include footer in nodes?'),
    '#description' => t('Check to include the footer when viewing nodes with issues of the newsletter. The footer is always included in e-mails with issues of the newsletter.'),
    '#default_value' => simplenews_template_footer_node($tid),
  );

  // Footer.
  $form['simplenews_template']['simplenews_template_footer']["simplenews_template_footer_$tid"] = array(
    '#type' => 'textarea',
    '#title' => t('Footer'),
    '#description' => t('Enter the content of the newsletter\'s footer. Available variables are:') . ' %site ' . t('(the name of your website),') . ' %uri ' . t('(a link to your homepage),') . ' %uri_brief ' . t('(homepage link without the http://),') . ' %mymail ' . t('(your e-mail address),') . ' %date ' . t('(today\'s date),') . ' %login_uri ' . t('(link to login page).'),
    '#default_value' => simplenews_template_footer($tid),
  );

  // Footer input format.
  $form['simplenews_template']['simplenews_template_footer']['simplenews_template_footer_format_$tid'] = filter_form(simplenews_template_footer_format($tid), 1, array("simplenews_template_footer_format_$tid"));

}

function _simplenews_template_form_alter_style(&$form, $tid) {

  // Style fieldset.
  $form['simplenews_template']['simplenews_template_style'] = array(
    '#type' => 'fieldset',
    '#title' => t('Style'),
    '#description' => t('The style to be applied to all issues of this newsletter'),
    '#collapsible' => true,
    '#collapsed' => true,
  );

  // CSS in node?
  $form['simplenews_template']['simplenews_template_style']["simplenews_template_css_node_$tid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Include CSS in nodes?'),
    '#description' => t('Check to include the CSS rules when viewing nodes with issues of the newsletter. The CSS rules are always included in e-mails with issues of the newsletter.'),
    '#default_value' => simplenews_template_css_node($tid),
  );

  // CSS.
  $form['simplenews_template']['simplenews_template_style']["simplenews_template_css_$tid"] = array(
    '#type' => 'textarea',
    '#title' => t('CSS'),
    '#description' => t('Enter the CSS rules of the body.'),
    '#default_value' => simplenews_template_css($tid),
  );

  // Background color.
  $form['simplenews_template']['simplenews_template_style']["simplenews_template_bgcolor_$tid"] = array(
    '#type' => 'textfield',
    '#title' => t('Body background color'),
    '#description' => t('Enter the <a href="http://www.w3.org/TR/html401/types.html#type-color">color</a> to use in the <a href="http://www.w3.org/TR/html401/present/graphics.html#background-color"><code>bgcolor</code></a> attribute of the <a href="http://www.w3.org/TR/html401/struct/global.html#edef-BODY"><code>&lt;body&gt;</code></a> element, e.g. <code>#ffff00</code> or <code>Yellow</code>.'),
    '#default_value' => simplenews_template_bgcolor($tid),
  );

}