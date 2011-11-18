<?php
// $Id: faq.questions_top.inc,v 1.1.4.5 2008/12/21 19:18:20 snpower Exp $

/**
 * @file
 * FAQ page callbacks for the "questions top" layouts.
 */

/**
 * Create the structure of the page, when the questions are to be shown on top.
 *
 * @param $nodes
 *   Array of node objects to display.
 * @return
 *   A variable holding the HTML formatted page.
 */
function theme_faq_questions_top($nodes) {

  // Fetch configuration.
  $teaser = variable_get('faq_use_teaser', FALSE);
  $links = variable_get('faq_show_node_links', FALSE);

  $this_page = $_GET['q'];

  // Configure "back to top" link.
  $back_to_top = faq_init_back_to_top($this_page);

  // Loop through results.
  $questions = array();
  foreach ($nodes as $node) {
    $anchor = "n". $node->nid;
    $questions[] = l($node->question, $this_page, NULL, NULL, $anchor);
    $answers .= theme('faq_format_question', $node, NULL, $anchor);
    $answers .= faq_view_answer($node, $back_to_top, $teaser, $links);
  }

  $list_style = variable_get('faq_question_listing', 'ul');
  $output = '<a name="top"></a>';
  $output .= theme('item_list', $questions, NULL, $list_style, array("class" => "faq-ul-questions-top"));
  $output .= "<div>\n". $answers ."</div>\n";

  return $output;
}

/**
 * Create the layout of the FAQ page if set to show the questions on top, all
 * sorted by categories.
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
function theme_faq_category_questions_top($nodes, $node_count, $display_header, $category_display, $term, $class, $term_image) {

  // Fetch configuration.
  $teaser = variable_get('faq_use_teaser', FALSE);
  $links = variable_get('faq_show_node_links', FALSE);
  $faq_count = variable_get('faq_count', FALSE);
  $hide_child_terms = variable_get('faq_hide_child_terms', FALSE);
  $show_term_page_children = variable_get('faq_show_term_page_children', FALSE);
  $answer_category_name = variable_get('faq_answer_category_name', FALSE);

  // Initialise some variables.
  $output = '';
  $this_page = $_GET['q'];
  $get_child_terms = 0;
  if (arg(0) == 'faq' && is_numeric(arg(1))) {
    $get_child_terms = arg(1);
  }

  $default_sorting = variable_get('faq_default_sorting', 'DESC');
  $default_weight = 0;
  if ($default_sorting != 'DESC') {
    $default_weight = 1000000;
  }

  // Configure "back to top" link.
  $back_to_top = faq_init_back_to_top($this_page);

  // Configure header.
  $output .= theme('faq_category_header', $term, $term_image, $display_header, $faq_count, $show_term_page_children, $hide_child_terms, $category_display, 'faq-category-menu');

  // Configure answer header.
  $answers_header = theme('faq_answer_category_header', $term, $term_image);


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
    $output .= faq_get_child_categories_faqs($term, 'faq_category_questions_top', $default_weight, $default_sorting, $category_display, $class);
  }


  // Retrieve questions and answers for this term.
  $group_questions_top = variable_get('faq_group_questions_top', FALSE);
  $questions = array();
  if (count($nodes)) {
    foreach ($nodes as $node) {
      $anchor = $term->tid ."n". $node->nid;
      $questions[] = l($node->question, $this_page, NULL, NULL, $anchor);
      if ($group_questions_top || $category_display == "hide_qa") {
        $answers .= theme('faq_format_question', $node, NULL, $anchor);
        $answers .= faq_view_answer($node, $back_to_top, $teaser, $links);
      }
    }
  }

  // Add question list to HTML output first, to appear at top of page.
  $list_style = variable_get('faq_question_listing', 'ul');
  $output .= theme('item_list', $questions, NULL, $list_style, array("class" => "faq-ul-questions-top"));


  // If questions and answers are to be grouped together, add answers to HTML
  // output before adding question list for sub-categories.  Same is true if
  // using the 'hide_qa' category layout.
  if ($group_questions_top || $category_display == "hide_qa") {

    // Output category name with answers.
    if ($answer_category_name) {
      if ($node_count) {
        $output .= $answers_header;
        $output .= "<div>\n". $answers ."\n</div>\n";
      }
      $output .= "</div>\n</div>\n";
    }

    // Don't output category name with answers.
    else {
      if ($node_count) {
        $output .= "<div>\n". $answers ."\n</div>\n";
      }
      $output .= "</div>\n</div>\n";
    }
  }

  // Questions from sub-categories should be listed with parent category's
  // questions, so close divs.
  else {
    $output .= "</div>\n</div>\n";
  }

  // Replace the %%FAQ_COUNT%% placeholder with the updated count (including
  // sub-categories where appropriate).
  if ($faq_count) $output = str_replace('%%FAQ_COUNT%%', $node_count, $output);

  return $output;
}

/**
 * Create the layout of the answers if set to show the questions on top, all
 * sorted by categories.
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
function theme_faq_category_questions_top_answers($nodes, $node_count, $display_header, $category_display, $term, $class, $term_image) {

  // Fetch configuration.
  $teaser = variable_get('faq_use_teaser', FALSE);
  $links = variable_get('faq_show_node_links', FALSE);
  $faq_count = variable_get('faq_count', FALSE);
  $hide_child_terms = variable_get('faq_hide_child_terms', FALSE);
  $show_term_page_children = variable_get('faq_show_term_page_children', FALSE);
  $answer_category_name = variable_get('faq_answer_category_name', FALSE);

  // Initialise some variables.
  $output = '';
  $this_page = $_GET['q'];
  $get_child_terms = 0;
  if (arg(0) == 'faq' && is_numeric(arg(1))) {
    $get_child_terms = arg(1);
  }

  $default_sorting = variable_get('faq_default_sorting', 'DESC');
  $default_weight = 0;
  if ($default_sorting != 'DESC') {
    $default_weight = 1000000;
  }

  // Configure "back to top" link.
  $back_to_top = faq_init_back_to_top($this_page);

  // Configure answer header.
  $answers_header = theme('faq_answer_category_header', $term, $term_image);


  // Retrieve questions and answers for this term.
  $questions = array();
  if (count($nodes) > 0) {
    foreach ($nodes as $node) {
      $anchor = $term->tid ."n". $node->nid;
      $answers .= theme('faq_format_question', $node, NULL, $anchor);
      $answers .= faq_view_answer($node, $back_to_top, $teaser, $links);
    }
  }

  // Questions from sub-categories should be listed with parent category's
  // questions.
  $group_questions_top = variable_get('faq_group_questions_top', FALSE);
  if (!$group_questions_top && $category_display != "hide_qa") {

    $answers_depth = 0;
    $indent = '<div class="faq-category-indent">'."\n";

    // Indent answers as appropriate.
    if ($answer_category_name) {
      while ($answers_depth < $term->depth) {
        $output .= $indent;
        $answers_depth++;
      }
    }

    $output .= '<div class="faq-category-group">'."\n";

    // Output category name with answers.
    if ($answer_category_name) {
      if (taxonomy_term_count_nodes($term->tid, 'faq')) {
        if (!empty($child_term_output_answers)) {
          $child_term_output_answers .= $answers;
          $answers = $child_term_output_answers;
        }
        $output .= $answers_header ."<div>\n". $answers ."\n</div>\n";
      }
    }

    // Don't output category name with answers.
    else {
      if (!empty($child_term_output_answers)) {
        $output .= $child_term_output_answers;
      }
      $output .= "<div>\n". $answers ."\n</div>\n";
    }
    $output .= "</div>\n";

    // Decrease answer section indent as appropriate.
    if ($answer_category_name) {
      while ($answers_depth > 0) {
        $output .= "</div>\n";
        $answers_depth--;
      }
    }
  }

  return $output;
}

