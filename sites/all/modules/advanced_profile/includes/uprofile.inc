$content[type]  = array (
  'name' => 'User Profile',
  'type' => 'uprofile',
  'description' => 'Holds the data for a user\'s profile. Needs to be attached to the user via Bio or Nodeprofile.',
  'title_label' => 'Profile Title',
  'body_label' => '',
  'min_word_count' => '0',
  'help' => '',
  'node_options' =>
  array (
    'status' => true,
    'promote' => false,
    'sticky' => false,
    'revision' => false,
  ),
  'comment' => '2',
  'upload' => 1,
  'privatemsg_link' =>
  array (
    'node' => false,
    'teaser' => false,
    'comment' => false,
  ),
  'old_type' => 'uprofile',
  'orig_type' => '',
  'module' => 'node',
  'custom' => '1',
  'modified' => '1',
  'locked' => '0',
  'fivestar' => 0,
  'fivestar_stars' => 5,
  'fivestar_labels_enable' => 1,
  'fivestar_label_0' => 'Cancel rating',
  'fivestar_label_1' => 'Poor',
  'fivestar_label_2' => 'Okay',
  'fivestar_label_3' => 'Good',
  'fivestar_label_4' => 'Great',
  'fivestar_label_5' => 'Awesome',
  'fivestar_label_6' => 'Give it @star/@count',
  'fivestar_label_7' => 'Give it @star/@count',
  'fivestar_label_8' => 'Give it @star/@count',
  'fivestar_label_9' => 'Give it @star/@count',
  'fivestar_label_10' => 'Give it @star/@count',
  'fivestar_style' => 'average',
  'fivestar_text' => 'dual',
  'fivestar_title' => 1,
  'fivestar_feedback' => 1,
  'fivestar_unvote' => 0,
  'fivestar_position_teaser' => 'hidden',
  'fivestar_position' => 'below',
  'fivestar_comment' => 0,
);
$content[groups]  = array (
  0 =>
  array (
    'label' => 'Basic Info',
    'settings' =>
    array (
      'form' =>
      array (
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' =>
      array (
        'description' => '',
        'teaser' => 'fieldset',
        'full' => 'fieldset',
        'label' => 'above',
      ),
    ),
    'weight' => '1',
    'group_name' => 'group_about',
  ),
  1 =>
  array (
    'label' => 'Stats',
    'settings' =>
    array (
      'form' =>
      array (
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' =>
      array (
        'description' => '',
        'teaser' => 'fieldset',
        'full' => 'fieldset',
        'label' => 'above',
      ),
    ),
    'weight' => '3',
    'group_name' => 'group_stats',
  ),
  2 =>
  array (
    'label' => 'Contact',
    'settings' =>
    array (
      'form' =>
      array (
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' =>
      array (
        'description' => '',
        'teaser' => 'fieldset',
        'full' => 'fieldset',
        'label' => 'above',
      ),
    ),
    'weight' => '5',
    'group_name' => 'group_contact',
  ),
  3 =>
  array (
    'label' => 'Links',
    'settings' =>
    array (
      'form' =>
      array (
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' =>
      array (
        'description' => '',
        'teaser' => 'fieldset',
        'full' => 'fieldset',
        'label' => 'above',
      ),
    ),
    'weight' => '7',
    'group_name' => 'group_links',
  ),
);
$content[fields]  = array (
  0 =>
  array (
    'widget_type' => 'options_buttons',
    'label' => 'Gender',
    'weight' => '-9',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => NULL,
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Male
Female
Undecided',
    'allowed_values_php' => '',
    'field_name' => 'field_gender',
    'field_type' => 'text',
    'module' => 'text, optionwidgets',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  1 =>
  array (
    'widget_type' => 'link',
    'label' => 'Homepage',
    'weight' => '-9',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_homepage' =>
      array (
        0 =>
        array (
          'url' => '',
        ),
      ),
    ),
    'group' => 'group_links',
    'required' => 0,
    'multiple' => 0,
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'display' =>
    array (
      'url_cutoff' => '80',
    ),
    'attributes' =>
    array (
      'target' => '_blank',
      'rel' => 'nofollow',
      'class' => '',
    ),
    'field_name' => 'field_homepage',
    'field_type' => 'link',
    'module' => 'link',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  2 =>
  array (
    'widget_type' => 'text',
    'label' => 'Name',
    'weight' => '-9',
    'rows' => '1',
    'description' => 'Your real name. ',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_name' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_about',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_name',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  3 =>
  array (
    'widget_type' => 'link',
    'label' => 'Blog',
    'weight' => '-7',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_blog' =>
      array (
        0 =>
        array (
          'url' => '',
        ),
      ),
    ),
    'group' => 'group_links',
    'required' => 0,
    'multiple' => 0,
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'display' =>
    array (
      'url_cutoff' => '80',
    ),
    'attributes' =>
    array (
      'target' => '_blank',
      'rel' => 'nofollow',
      'class' => '',
    ),
    'field_name' => 'field_blog',
    'field_type' => 'link',
    'module' => 'link',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  4 =>
  array (
    'widget_type' => 'text',
    'label' => 'Location',
    'weight' => '-7',
    'rows' => '1',
    'description' => 'Where you live.',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_location' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_about',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_location',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  5 =>
  array (
    'widget_type' => 'text',
    'label' => 'Occupation',
    'weight' => '-7',
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_occupation' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '100',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_occupation',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  6 =>
  array (
    'widget_type' => 'options_select',
    'label' => 'Children',
    'weight' => '-6',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_children' =>
      array (
        'key' => false,
      ),
    ),
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'No children: not planning on having any
No children: would like some now or in the future
Have young child(ren)
Have grown children
My pets are my kids
',
    'allowed_values_php' => '',
    'field_name' => 'field_children',
    'field_type' => 'text',
    'module' => 'text, optionwidgets',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  7 =>
  array (
    'widget_type' => 'text',
    'label' => 'About Me',
    'weight' => '-5',
    'rows' => '10',
    'description' => 'General information about who you are, where you came from, and where you are going.',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_about_me' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'field_about_me' =>
    array (
      0 =>
      array (
        'format' => 1,
      ),
    ),
    'group' => 'group_about',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '1',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_about_me',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  8 =>
  array (
    'widget_type' => 'options_select',
    'label' => 'Education',
    'weight' => '-5',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_education' =>
      array (
        'key' => false,
      ),
    ),
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Before high school
In high school
Some high school
Completed high school
In college
Some college
Completed college
In post graduate
Some post graduate
Completed post graduate
',
    'allowed_values_php' => '',
    'field_name' => 'field_education',
    'field_type' => 'text',
    'module' => 'text, optionwidgets',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  9 =>
  array (
    'widget_type' => 'link',
    'label' => 'Facebook',
    'weight' => '-5',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_facebook' =>
      array (
        0 =>
        array (
          'url' => '',
        ),
      ),
    ),
    'group' => 'group_links',
    'required' => 0,
    'multiple' => 0,
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'display' =>
    array (
      'url_cutoff' => '80',
    ),
    'attributes' =>
    array (
      'target' => '_blank',
      'rel' => '',
      'class' => '',
    ),
    'field_name' => 'field_facebook',
    'field_type' => 'link',
    'module' => 'link',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  10 =>
  array (
    'widget_type' => 'text',
    'label' => 'Ethnicity',
    'weight' => '-4',
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_ethnicity' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_ethnicity',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  11 =>
  array (
    'widget_type' => 'text',
    'label' => 'Interests',
    'weight' => '-3',
    'rows' => '5',
    'description' => 'Describe your interests and hobbies. This section is for whole sentences, not tags.',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_interests' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'field_interests' =>
    array (
      0 =>
      array (
        'format' => 1,
      ),
    ),
    'group' => 'group_about',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '1',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_interests',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  12 =>
  array (
    'widget_type' => 'text',
    'label' => 'LinkedIn',
    'weight' => '-3',
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_linkedin' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_links',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_linkedin',
    'field_type' => 'text',
    'module' => 'text',
  ),
  13 =>
  array (
    'widget_type' => 'options_select',
    'label' => 'Status',
    'weight' => '-3',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_status' =>
      array (
        'key' => false,
      ),
    ),
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Single: not looking
Single: looking
In a relationship
Married
Divorced
Widowed
',
    'allowed_values_php' => '',
    'field_name' => 'field_status',
    'field_type' => 'text',
    'module' => 'text, optionwidgets',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  14 =>
  array (
    'widget_type' => 'options_select',
    'label' => 'Orientation',
    'weight' => '-2',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_orientation' =>
      array (
        'key' => false,
      ),
    ),
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Straight
Gay
Bi
Undecided
',
    'allowed_values_php' => '',
    'field_name' => 'field_orientation',
    'field_type' => 'text',
    'module' => 'text, optionwidgets',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  15 =>
  array (
    'widget_type' => 'link',
    'label' => 'Myspace',
    'weight' => '-1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_myspace' =>
      array (
        0 =>
        array (
          'url' => '',
        ),
      ),
    ),
    'group' => 'group_links',
    'required' => 0,
    'multiple' => 0,
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'display' =>
    array (
      'url_cutoff' => '80',
    ),
    'attributes' =>
    array (
      'target' => '_blank',
      'rel' => 'nofollow',
      'class' => '',
    ),
    'field_name' => 'field_myspace',
    'field_type' => 'link',
    'module' => 'link',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  16 =>
  array (
    'widget_type' => 'text',
    'label' => 'Political Leaning',
    'weight' => '-1',
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_politcal_leaning' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_politcal_leaning',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  17 =>
  array (
    'widget_type' => 'text',
    'label' => 'AIM',
    'weight' => 0,
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_aim' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_contact',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_aim',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  18 =>
  array (
    'widget_type' => 'text',
    'label' => 'Google',
    'weight' => 0,
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_google' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_contact',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_google',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  19 =>
  array (
    'widget_type' => 'text',
    'label' => 'ICQ',
    'weight' => 0,
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_icq' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_contact',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_icq',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  20 =>
  array (
    'widget_type' => 'text',
    'label' => 'MSN',
    'weight' => 0,
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_msn' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_contact',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_msn',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  21 =>
  array (
    'widget_type' => 'text',
    'label' => 'Religion',
    'weight' => 0,
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_religion' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_religion',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  22 =>
  array (
    'widget_type' => 'text',
    'label' => 'Skype',
    'weight' => 0,
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_skype' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_contact',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_skype',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  23 =>
  array (
    'widget_type' => 'text',
    'label' => 'Yahoo',
    'weight' => 0,
    'rows' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_yahoo' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'group' => 'group_contact',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_yahoo',
    'field_type' => 'text',
    'module' => 'text',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  24 =>
  array (
    'widget_type' => 'options_select',
    'label' => 'Zodiac Sign',
    'weight' => '1',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_zodiac_sign' =>
      array (
        'key' => false,
      ),
    ),
    'group' => 'group_stats',
    'required' => 0,
    'multiple' => 0,
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Aries (Mar 21-Apr 19)
Taurus (Apr 20-May 20)
Gemini (May 21-Jun 20)
Cancer (Jun 21-Jul 22)
Leo (Jul 23-Aug 22)
Virgo (Aug 23-Sep 22)
Libra (Sep 23-Oct 22)
Scorpio (Oct 23-Nov 21)
Sagittarius (Nov 22-Dec 21)
Capricorn (Dec 22-Jan 19)
Aquarius (Jan 20-Feb 18)
Pisces (Feb 19-Mar 20)',
    'allowed_values_php' => '',
    'field_name' => 'field_zodiac_sign',
    'field_type' => 'text',
    'module' => 'text, optionwidgets',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  25 =>
  array (
    'widget_type' => 'link',
    'label' => 'Favorite #1',
    'weight' => '4',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_favorite1' =>
      array (
        0 =>
        array (
          'url' => '',
          'title' => '',
        ),
      ),
    ),
    'group' => 'group_links',
    'required' => 0,
    'multiple' => 0,
    'url' => 0,
    'title' => 'optional',
    'title_value' => '',
    'display' =>
    array (
      'url_cutoff' => '80',
    ),
    'attributes' =>
    array (
      'target' => '_blank',
      'rel' => 'nofollow',
      'class' => '',
    ),
    'field_name' => 'field_favorite1',
    'field_type' => 'link',
    'module' => 'link',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  26 =>
  array (
    'widget_type' => 'link',
    'label' => 'Favorite #2',
    'weight' => '6',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_favorite2' =>
      array (
        0 =>
        array (
          'url' => '',
          'title' => '',
        ),
      ),
    ),
    'group' => 'group_links',
    'required' => 0,
    'multiple' => 0,
    'url' => 0,
    'title' => 'optional',
    'title_value' => '',
    'display' =>
    array (
      'url_cutoff' => '80',
    ),
    'attributes' =>
    array (
      'target' => '_blank',
      'rel' => 'nofollow',
      'class' => '',
    ),
    'field_name' => 'field_favorite2',
    'field_type' => 'link',
    'module' => 'link',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
  27 =>
  array (
    'widget_type' => 'link',
    'label' => 'Favorite #3',
    'weight' => '8',
    'description' => '',
    'default_value' =>
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_favorite3' =>
      array (
        0 =>
        array (
          'url' => '',
          'title' => '',
        ),
      ),
    ),
    'group' => 'group_links',
    'required' => 0,
    'multiple' => 0,
    'url' => 0,
    'title' => 'optional',
    'title_value' => '',
    'display' =>
    array (
      'url_cutoff' => '80',
    ),
    'attributes' =>
    array (
      'target' => '_blank',
      'rel' => 'nofollow',
      'class' => '',
    ),
    'field_name' => 'field_favorite3',
    'field_type' => 'link',
    'module' => 'link',
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'inline',
      ),
      'teaser' =>
      array (
        'format' => 'default',
      ),
      'full' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
);
