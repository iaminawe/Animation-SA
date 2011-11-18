/* $Id: README.txt,v 1.1 2006/12/04 23:10:58 douggreen Exp $

The views_fastsearch module provides an alternative search filter and search
sort to the default search methods provided in views_search.inc.  This search
is considerably faster and supports AND/OR terms, exception terms, quoted
terms, and sorting by score.

Installation
------------

1.  Install this file into the modules directory of your choice (for example,
sites/yoursite.com/modules/views_search or modules/views_search).
2.  Enable the module in the admin/modules page
3.  Create a view and select the 'Search: Fast Index' filter, optionally
select the 'Search: Score' sort.

Author
------
Doug Green
doug@civicactions.net
douggreen@douggreenconsulting.com
