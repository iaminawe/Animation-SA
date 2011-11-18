OVERVIEW
--------
The Views module allows administrators to create dynamic lists of content for
display in pages or blocks. It is possible to insert those lists into existing
node bodies and blocks, but such inclusion requires that PHP filtering be turned
on. The Insert View module allows any user to insert view listings using tag
syntax, without the need for PHP execution permissions. The Insert View tag
syntax for embedding a view is relatively simple:

[view:<name of view>] is replaced by the content listing corresponding to the
named view.

[view:<name of view>=<number>] limits the listing to a particular <number> of
entries.

[view:<name of view>=<number>=<comma-delimited-list>] limits the listing to a
particular <number> of entries, and passes a comma delimited list of arguments to the view.

Here's an example you could use with the default view named "tracker" which
takes a user ID as an argument:

[view:tracker=5=1]

In short this tag says, "Insert the view named tracker, limit the number of
results to 5, and supply the argument/user ID 1."

Sometimes you want to pass an argument without placing a limit on the number
of results. You can do that by leaving the <number> position empty, like so:

[view:<name of view>==<comma-delimited-list>]

You can use a pager with your view by using the following syntax (note:
you must set a limit which will serve as the number of nodes per page):

[view_pager:<name of view>=<number>].

INSTALLATION
------------
Extract and save the Insert View folder in your site's modules folder and enable it at
admin/build/modules. Obviously, it requires the Views module to do its magic.

Once Insert View is installed, visit the the input formats page at /admin/settings/filters
and click the "configure" link for the input format(s) for which you wish to enable the
Insert View Filter.  Then simply check the checkbox for the filter.

UPGRADING FROM A PREVIOUS VERSION?
----------------------------------
In previous versions of Insert View (including the 2008-Jan-11 development snapshot
and earlier) it was was not required to enable the Insert View filter for input formats
(by visiting the /admin/settings/filters pages) because Insert View was a pseudo filter
and used hook_nodeapi() rather than the filter system.

Insert View now runs as a classic Drupal filter module, and that means it now works
in blocks.  If you upgrade your site and find Insert View tags aren't working, please
visit /admin/settings/filters and enable the Insert View Filter for each input format
necessary.