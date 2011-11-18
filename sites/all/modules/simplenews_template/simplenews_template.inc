<?php

// $Id: simplenews_template.inc,v 1.1.2.2 2009/02/11 18:54:45 tbarregren Exp $


/**
 * @file
 * Private implementations of the Simplenews Template module. Don't call these
 * functions. They are subject to changes.
 */


/*****************************************************************************
 * MENU CALLBACKS
 *****************************************************************************/

/**
 * Output a Simplenews template'd newsletter node like in a mail.
 */
function _simplenews_template_preview($nid = 0, $vid = null) {
  $node = node_load($nid, $vid);
  if (!$node || $node->type != 'simplenews') {
    return drupal_not_found();
  }
  $node = simplenews_node_prepare($nid, $vid, $node->tid);
  $node = theme('simplenews_newsletter_footer', $node, '');
  echo $node->body;
}


/*****************************************************************************
 * IMPLEMENTING THE NODE API
 *****************************************************************************/

/**
 * A newsletter issue is being viewed.
 */
function _simplenews_template_node_view(&$node, $teaser, $page) {

  // Don't include header and footer if this is a teaser.
  if ($teaser) return;

  // Get the themed body.
  $body = theme('simplenews_template_body', $node->content['body']['#value']);

  // Add the themed header if it should be included in nodes.
  if (simplenews_template_header_node($node->tid)) {
    $body = _simplenews_template_content('header', $node) . $body;
  }

  // Add the themed footer if it should be included in nodes.
  if (simplenews_template_footer_node($node->tid)) {
    $body = $body . _simplenews_template_content('footer', $node);
  }

  // Add the CSS rules if they should be included in nodes.
  if (simplenews_template_css_node($node->tid)) {
    $css = simplenews_template_css($node->tid);
    $css = '<style type="text/css">'. $css . "</style>\n";
    drupal_set_html_head($css);
  }

  // Update the node's content.
  $node->content['body']['#value'] =  $body;

}


/*****************************************************************************
 * IMPLEMENTING THE SIMPLENEWS NEWSLETTER TEMPLATE.
 *****************************************************************************/

/**
 * Overriding theme_simplenews_newsletter().
 */
function _simplenews_template_newsletter($node, $tid) {

  // Get the newsletter and issue names.
  $newsletter_name = taxonomy_get_term($tid)->name;
  $issue_name = $node->title;

  // Prepare the <style> element. Because mimemail_html_to_text() only matches
  // <style>...</style> when the opening and closing tags are on the same line,
  // we prepare the style element already here, instead of in the theme.
  $css = simplenews_template_css($tid);
  $style_element = '<style type="text/css">'. preg_replace('/\n|\r/', ' ', $css) .'</style>';

  // Get the newsletter specific settings.
  $bgcolor = simplenews_template_bgcolor($tid);

  // Theme the subject.
  $node->subject = theme('simplenews_template_mail_subject', $newsletter_name, $issue_name);

  // Add the themed header if it isn't already included in the node.
  if (!simplenews_template_header_node($tid)) {
    $node->body = _simplenews_template_content('header', $node) . $node->body;
  }

  // Add the themed footer if it isn't already included in the node.
  if (!simplenews_template_footer_node($tid)) {
    $node->body = $node->body . _simplenews_template_content('footer', $node);
  }

  // Theme the e-mail.
  $node->body = theme('simplenews_template', $node, $newsletter_name, $issue_name, $style_element, $bgcolor);

  // If the Emogrifier <http://www.pelagodesign.com/sidecar/emogrifier/>
  // exists, let it inline the CSS definitions into the HTML tags.
  $node->body = _simplenews_template_emogrify($node->body, $css);

  return $node;

}


/**
 * Overriding theme_mimemail_message().
 */
function _simplenews_template_message($content) {

  // If content already is a complete html page, just return it.
  if (_simplenews_template_starts_with($content, '<!DOCTYPE', '<html', '<?xml')) {
    return $content;
  }

  // Embed the content in a html page.
  return theme('simplenews_template_mimemail_message', $content);

}


/*****************************************************************************
 * HELPERS
 *****************************************************************************/

/**
 * Returns the filtered content after substitution of Simplenews' variables.
 */
function _simplenews_template_content($type, &$node) {
  $getter = "simplenews_template_${type}";
  $filter = "simplenews_template_${type}_format";
  $themer = "simplenews_template_${type}";
  $tmp->uid = $node->uid;
  $tmp->body = $getter($node->tid);
  $tmp->body = check_markup($tmp->body, $filter($node->tid), false);
  $tmp = simplenews_replace_vars($tmp);
  return theme($themer, $tmp->body);
}


/**
 * Returns true iff $text starts with any of the arguments following $text,
 * white spaces and comments excluded.
 */
function _simplenews_template_starts_with($text) {

  // White space characters.
  static $ws = " \t\n\r\0\x0B";

  // Skip white spaces and comments.
  $pos = 0;
  while (true) {
    $pos += strspn($text, $ws, $pos);
    if (substr($text, $pos, 4) !== '<!--') break;
    $pos = strpos($text, '-->', $pos) + 3;
  }

  // Return true if any of the strings to look for are found.
  $args = func_get_args();
  array_shift($args);
  foreach ($args as $start) {
    if (strcasecmp($start, substr($text, $pos, strlen($start))) === 0) return true;
  }

  // Return false since none of the strings to look for was found.
  return false;

}


/**
 * If the Emogrifier <http://www.pelagodesign.com/sidecar/emogrifier/> exists,
 * the CSS definitions in $css are inserted into tags within $html based on
 * the CSS selectors.
 */
function _simplenews_template_emogrify($html, $css) {
  $path = drupal_get_path('module', 'simplenews_template');
  $path = "./$path/emogrifier.php";
  if (is_file($path)) {

    // Emogrify can't handle several CSS rules on one line. As a precaution,
    // we therefore insert LF after each closing bracket.
    $css = preg_replace('/}\s*/', "}\n", $css);

    // Inline the CSS rules.
    include_once $path;
    $emogrifier = new Emogrifier($html, $css);
    $html = $emogrifier->emogrify();

  }
  return $html;
}