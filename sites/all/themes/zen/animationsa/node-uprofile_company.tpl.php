<div class="node">

<?php if ($page){
drupal_goto("user/$node->uid", NULL, NULL, 301);
} else { ?>

<h3 class="title"><a href="<?php print $node_url ?>"><?php print $title ?></a></h3>
       <?php print $content; ?>
<?php }; ?>

</div>