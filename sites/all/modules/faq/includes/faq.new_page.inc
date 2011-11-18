<?php
// $Id: faq.new_page.inc,v 1.1.4.4 2008/12/21 19:18:20 snpower Exp $

/**
 * @file
 * FAQ page callbacks for the "new page" layouts.
 */

/**
 * Create the code of the FAQ page if set to show the answer in a new page.
 *
 * @param $nodes
 *   Array of node objects to display.
 * @return
 *   A variable holding the HTML formatted page.
 */
function theme_faq_new_page($nodes) {
  // Fetch configuration.
  $teaser = variable_get('faq_use_teaser', FALSE);
  $links = variable_get('faq_show_node_links', FALSE);

  $items = array();
  foreach ($nodes as $node) {
    $items[] = l($node->question, "node/$node->nid");

  }
  $list_style = variable_get('faq_question_listing', 'ul');
  $output .= theme('item_list', $items, NULL, $list_style, array("class" => "faq-question-listing"));

  return $output;
}


/**
 * Create the code of the FAQ page if set to show the answer in a new page
 * when the category-sorted question is clicked.
 *
 * @param $nodes
 *   Array of node objects to display.
 * @param $node_count
 *   Number of nodes for this term, and possibly also the sub-terms.
 * @param $display_header
 *   Boolean value controlling category header layout.
 * @param $category_display
 *   The layout of categories which should be used.
 * @param $term
 *   The category / term to display FAQs for.
 * @param $class
 *   CSS class which the HTML div will be using. A special class name is
 *   required in order to hide and questions / answers.
 * @param $term_image
 *   HTML output containing any taxonomy images attached to the taxonomy term.
 * @return
 *   A variable holding the HTML formatted page.
 */
function theme_faq_category_new_page($nodes, $node_count, $display_header, $category_display, $term, $class, $term_image) {

  // Fetch configuration.
  $teaser = variable_get('faq_use_teaser', FALSE);
  $links = variable_get('faq_show_node_links', FALSE);
  $faq_count = variable_get('faq_count', FALSE);
  $hide_child_terms = variable_get('faq_hide_child_terms', FALSE);
  $show_term_page_children = variable_get('faq_show_term_page_children', FALSE);

  // Initialise some variables.
  $get_child_terms = 0;
  if (arg(0) == 'faq' && is_numeric(arg(1))) {
    $get_child_terms = arg(1);
  }

  $default_sorting = variable_get('faq_default_sorting', 'DESC');
  $default_weight = 0;
  if ($default_sorting != 'DESC') {
    $default_weight = 1000000;
  }


  // Configure header.
  $output .= theme('faq_category_header', $term, $term_image, $display_header, $faq_count, $show_term_page_children, $hide_child_terms, $category_display);


  // Configure Q/A div container with appropriate class name for hiding/unhiding
  // questions and answers.
  if ($get_child_terms == $term->tid) {
    $output .= '<div class="faq-qa">'."\n";
  }
  else {
    $output .= '<div class="'. $class .'">'."\n";
  }

  // Determine if faqs for sub-categories should be displayed or not.
  if (($get_child_terms && $category_display == 'categories_inline') || ((($show_term_page_children && $this_page != 'faq') || $hide_child_terms) && $category_display == 'hide_qa')) {
    $output .= faq_get_child_categories_faqs($term, 'faq_category_new_page', $default_weight, $default_sorting, $category_display, $class);
  }


  // Retrieve questions and answers for this term.
  $items = array();
  if (count($nodes)) {
    foreach ($nodes as $node) {
      $items[] = l($node->question, "node/$node->nid");
    }
  }
  $list_style = variable_get('faq_question_listing', 'ul');
  $output .= theme('item_list', $items, NULL, $list_style, array("class" => "faq-ul-new-page"));
  $output .= "</div>\n</div>\n";

  // Replace the %%FAQ_COUNT%% placeholder with the updated count (including
  // sub-categories where appropriate).
  if ($faq_count) $output = str_replace('%%FAQ_COUNT%%', $node_count, $output);

  return $output;
}

