/* $Id: README.txt,v 1.5.2.1 2008/03/16 21:16:50 douggreen Exp $

The views_filterblock module basically moves the horizontal filter from the
views page content area into a (vertical) block.  This differs from the views
block option which displays the view exposed filters AND a limited number of
rows from views content.  It themes the block using collapsible fieldsets
rather than the table currently used by views, and it uses some logic to
decide which fieldsets should be collapsed or not collapsed based on whether
the filter form has a value.

Installation
------------

1.  Install this file into the modules directory of your choice (for example,
sites/yoursite.com/modules/views_filterblock or modules/views_filterblock).
2.  Enable the module in the admin/modules page
3.  Optionally set the number of blocks you need in
admin/settings/views_filterblock.
3.  Add the 'Views Filter Form' blocks on the admin/block page and configure
them.  You may want to restrict this block to only display on your views page
by using the block configure options, but this is not a requirement.
