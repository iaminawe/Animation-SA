This module contains plugins and default views for the Views module.
Some of the plugins may require other modules.

These plugins will only appear on your views administration page, in the
'type' dropdown of the page and block sections.

The plugins supplied with the module as of this writing are:

Panels: Teasers, 1 top + 2 columns
  Requires panels.module -- will spread a view across a 2 column
  stacked layout, meaning the first node will appear across the top,
  and the rest of the nodes will alternate left and right.

Panels: Teasers, 2 columns
  Requires panels.module -- like above, but only alternates left/right.

Panels: Teasers, 1 top + 3 columns
  Requires panels.module -- like above, but offers 1 across the top,
  then alternates left, middle, right.

Panels: Teasers, 3 columns
  Requires panels.module -- like above, but merely left/middle/right
  alternating.

Panels: By term, 3 columns
  Requires panels.module -- terms presented as tables within columns such as http://sfbay.craigslist.org/.

Bonus: Grid View
  Displays items in a very simple 4 across table; the CSS sets the
  table to 100%, but this is easily overridden if you like. It is good
  for picture galleries, as an example.

Bonus: Summary + full view
  Stacks a summary version of a view above a full view or additional 
  summary version of the view to allow them to be viewed at the same 
  time. Clicking on a link on the top summary view changes the result 
  in the bottom of the page based on the selected item. This 
  makes it possible to combine something like an alpha and full term 
  name as follows (where selecting 'B' in the top will change the
  bottom view to display terms that start with the letter 'B'):
  
  A (10) | B (33) | C (4) | ...
  -------------------------------
  Accessiblility (5)
  Action (2)
  Assistance (3)
  
  Use the taxonomy_directory default view as an example or starting point. 

Lineage: Nested taxonomy summary
  Requires lineage.module. Displays summary views of taxonomy arguments
  in a nested tree, sorted by hierarchy. 
  
  Add Lineage:depth as a field to a view to get the nesting effect
  and add Lineage: Taxonomy Hierarchy to sorts to get hierarchical sort.
  
  Use the taxonomy_tree default view as an example or starting point. 
  The default view has 2 arguments. The first displays all terms and 
  allows you to select a branch of the tree to view and passes that 
  value to the second argument which displays a nested view of only 
  the selected branch.

Audio: Playlists
  REQUIRES: audio.module + this flash mp3 player: 
    http://jeroenwijering.com/?item=Flash_MP3_Player
  Download the player from the site above and place it in your audio module
  base directory.

  Create a new view. Set the 'type' to Audio: Playlist. Add a filter so that
  only 'audio' node types will be in the view. You don't want to use paging
  with this view.