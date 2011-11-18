<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language; ?>" xml:lang="<?php print $language; ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <!--[if IE]>
    <link rel="stylesheet" href="<?php print $base_path . $directory; ?>/ie.css" type="text/css">
    <?php if ($subtheme_directory && file_exists($subtheme_directory .'/ie.css')): ?>
      <link rel="stylesheet" href="<?php print $base_path . $subtheme_directory; ?>/ie.css" type="text/css">
    <?php endif; ?>
  <![endif]-->
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_classes; ?>">

  <div id="page"><div id="page-inner">

    <a name="top" id="navigation-top"></a>

    <div id="header"><div id="header-inner" class="clear-block">
      <?php if ($logo || $site_name || $site_slogan): ?>
        <div id="logo-title">

          <?php if ($logo): ?>
            <div id="logo"><a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" id="logo-image" /></a></div>
          <?php endif; ?>

          <?php if ($site_name): ?>
            <?php
              // Use an H1 only on the homepage
              $tag = $is_front ? 'h1' : 'div';
            ?>
            <<?php print $tag; ?> id='site-name'><strong>
              <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home">
                <?php print $site_name; ?>
              </a>
            </strong></<?php print $tag; ?>>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <div id='site-slogan'><?php print $site_slogan; ?></div>
          <?php endif; ?>

        </div> <!-- /#logo-title -->
      <?php endif; ?>
       <div id="loginstrip">
 <div id="mainsearch"> <?php print $search_box ?></div>
 
 <?php  global $user; ?>
<?php if ($user->uid) : ?>
  <span class="login_text">Hi</span> <?php print l($user->name,'user/'.$user->uid); ?>
    <?php else : ?>
  <?php print drupal_get_form('user_login_block');?>
      <?php endif; ?>
      </div>

<div id="primarynav">
<?php

print theme('nice_menu_primary_links', 'downdown'); 

?>
</div>
      <?php if ($header): ?>
        <div id="header-blocks">
          <?php print $header; ?>
        </div> <!-- /#header-blocks -->
      <?php endif; ?>

    </div></div> <!-- /#header-inner, /#header -->

    <div id="main"><div id="main-inner" class="clear-block">

      <div id="content"><div id="content-inner">

        <?php if ($mission): ?>
          <div id="mission"><?php print $mission; ?></div>
        <?php endif; ?>

        <?php if ($content_top): ?>
          <div id="content-top">
            <?php print $content_top; ?>
          </div> <!-- /#content-top -->
        <?php endif; ?>

        <?php if ($title or $tabs or $help or $messages): ?>
          <div id="content-header">
         
            <?php if ($title): ?>
            <?php
            
if ($title != '') {
    $profile = signwriter_load_profile('CarbonBlockTitle');
    // at this point you could override any settings. for example:
    // $profile->fontsize = 43; // override the font size
    print signwriter_title_convert($title, $profile);
}
?>

            <?php endif; ?>
            <?php print $messages; ?>
            <?php if ($breadcrumb or $tabs): ?>
              <div class="tabs"><?php print $tabs; ?></div>
                 <?php print $breadcrumb; ?>
            <?php endif; ?>
            <?php print $help; ?>
          </div> <!-- /#content-header -->
        <?php endif; ?>

        <div id="content-area">
          <?php print $content; ?>
        </div>

        <?php if ($feed_icons): ?>
          <div class="feed-icons"><?php print $feed_icons; ?></div>
        <?php endif; ?>

        <?php if ($content_bottom): ?>
          <div id="content-bottom">
            <?php print $content_bottom; ?>
          </div> <!-- /#content-bottom -->
        <?php endif; ?>

      </div></div><!-- /#content-inner, /#content -->

      <?php if ($sidebar_left): ?>
        <div id="sidebar-left"><div id="sidebar-left-inner">
          <?php print $sidebar_left; ?>
        </div></div> <!-- /#sidebar-left-inner, /#sidebar-left -->
      <?php endif; ?>

      <?php if ($sidebar_right): ?>
        <div id="sidebar-right"><div id="sidebar-right-inner">
          <?php print $sidebar_right; ?>
        </div></div> <!-- /#sidebar-right-inner, /#sidebar-right -->
      <?php endif; ?>

    </div></div> <!-- /#main-inner, /#main -->

    <div id="footer"><div id="footer-inner">

      <div id="footer-message"><?php print $footer_message; ?></div>

    </div></div> <!-- /#footer-inner, /#footer -->

    <?php if ($closure_region): ?>
      <div id="closure-blocks"><?php print $closure_region; ?></div>
    <?php endif; ?>

    <?php print $closure; ?>

  </div></div> <!-- /#page-inner, /#page -->

</body>
</html>