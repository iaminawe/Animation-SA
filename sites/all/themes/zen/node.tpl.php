<div class="node <?php print $node_classes ?>" id="node-<?php print $node->nid; ?>"><div class="node-inner">

  <?php if ($page == 0): ?>
    <h2 class="title">
      <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>

  <?php if ($unpublished) : ?>
    <div class="unpublished"><?php print t('Unpublished'); ?></div>
  <?php endif; ?>

  <?php if ($picture) print $picture; ?>



  <div class="content">
    <?php print $content; ?>
  </div>
  
  <?php if ($submitted && !$teaser): ?>
    <span class="submitted"><?php print t('Posted ') . format_date($node->created, 'custom', "F jS, Y") . t(' by ') . theme('username', $node); ?></span> 
  <?php endif; ?>


<?php if ($submitted && $teaser): ?>
 <span class="submitted"><?php print  t(' by ') . theme('username', $node) .(' on ') . format_date($node->created, 'custom', "F jS, Y") ; ?>
</span> 
<?php endif; ?>
  
<?php if ($links && !$teaser): ?>
<div class="links"><?php print $links; ?></div>
<?php endif; ?>

</div></div> <!-- /node-inner, /node -->