$Id: README.txt,v 1.5.2.1 2007/02/28 17:35:36 fago Exp $

Views Fusion Module
------------------------
by Wolfgang Ziegler, nuppla@zites.net


Description
-----------
Views Fusion allows one to fuse multiple views into one. So you can
build fusioned views that display information that is stored in multiple
nodes - useful for tabular views. It uses node relations for joining the
appropriate nodes together.

So currently the views_fusion module needs the nodefamily module 
(http://drupal.org/project/nodefamily) for obtaining the node relation 
information. However in future other node relation modules could also 
provide their data for views fusion as it is written generic.


Installation 
------------
 * Install the latest views module, you need at least version 1.2
 * Copy the module to your modules directory and activate it.

Note: You also need a node relation module, e.g. nodefamily.


How to use it
-------------
First you have to define multiple views, one for each type of nodes. Then
the views fusion module is used to fuse these views to a big one which 
contains all the information.
To do this go to 'admin/views/fusion' and define which views you want to 
fuse and which information you want to use for fusing the views, e.g. 
use a nodefamily relation.
Then have a look at the primary view, it will list the fields of the fused
view too.

Note that you have to select an appropriate node relation which connects
the nodes together. If you set a not existing relation, your fused view
will have no results. So set this settings carefully.


Notes
-----
 * You have the fuse the views in the correct order. You have to fuse your views
   in the same order as your chosen relation does work.
   
   e.g.:
   ViewA lists nodes of the type 'CD'
   ViewB lists nodes of the type 'artist'
   
   Nodefamily creates a relation between some of them, where CDs are parents and
   artists their children.
   
   Then you can create a fusion by using ViewA as primary view, fused with ViewB
   using the nodefamily parent - child relation.
   Or you can also create a fusion in the reverse direction: Use ViewB as primary 
   view, fused with ViewA using the nodefamily child - parent relation.


 * Currently it's not possible to alter the order of single fields of a tabular 
   view over the whole view. The first field of a fused view will always be displayed
   behind the last field of the primary view.
   This also applies to any sort critera you might have set for the views. So the sort
   criteria of the primary view will have precedence over the sort criteria from the
   fused view.
   However the order of the fields can still be customized by theming the view.

 
Restrictions & Problems
-----------------------
 * Argument Handlers for fused views are not supported! You may only use argument handlers
   on the primary view.
 * Some fields don't work properly with views_fusion. Currently known to not work are:
 
       * CCK fields for multiple fields, which are set to "group multiple values"
       
 * If you discover further not working fields or filters, please open an issue for them in 
   the views fusion issue queue, so I can fix them or add them here.
 