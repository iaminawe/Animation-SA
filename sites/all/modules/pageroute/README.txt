$Id: README.txt,v 1.14.2.4 2007/04/24 17:45:08 fago Exp $

Pageroute Module
------------------------
by Wolfgang Ziegler, nuppla@zites.net


Other documentation files:
--------------------------
API.txt ... Description of the pageroute API, for developers
UPGRADE.txt ... for upgraders from 4.7.x


Short module overview:
---------------------
pageroute.module - Allows the creation of pageroutes.
pageroute_ui.module - Adminstration pages for pageroute

Optional:
pageroute_nodefamily.module - Still in development


Description
-----------
The module can be used to provide a user friendly wizard for creating and
editing several nodes. 
You can use the module to create a "route" which leads users through multiple
pages, which can be e.g. node creation forms.

For example this allows you to build a user profile which consists of multiple
content types. Then users can easily create and edit their nodes through the
same pageroute. (Have a look at the nodeprofile project if you are interested
in building user profiles with nodes).


Installation
------------
 * First install the subform element module, on which pageroute depends:
   http://drupal.org/project/subform_element
 * Then copy the whole pageroute directory to your modules directory and
   activate at least the modules pageroute and pageroute_ui.


Introduction
------------

Pageroute allows you define a route through various pages. There are several different
type of pages available. Pageroute comes with the following page types:
 * node add form
 * node edit form
 * node management page
 * user edit page
 
The node management page allows one to add/edit/delete nodes from a configurable
content type. It shows a themeable list of all already created nodes of this type
and allows editing and deleting if the user has access.

For further information regarding the page types have a look at the pageroute_ui 
help page. Make sure that you have enabled the help module, then go to:
http://yoursite.example.com/admin/help/pageroute_ui

To create or edit your pageroutes activate the pageroute_ui module and go to
/admin/build/pageroute. Pageroute will automatically generate a new menu item
for each pageroute, which can be customized by using the menu module. Furthermore
it creates customizable back/forward buttons at the bottom of each page,
so that users are lead through the route.

Once you have finished defining your route you may deactivate pageroute_ui.module
again, as it provides only the adminstration pages.



Hints
-----

 (*) Pageroute Arguments:

Each pageroute takes further arguments to its path. Each page type can make use of 
these arguments, but they need not. Have a look at the page type description to see
how it handles the arguments.
Page types will interprete the first additional argument as node id, which is used 
by most node page types, e.g. by the node editing page. The second argument will be 
interpreted as id of the user for which the route will be gone through. E.g. this 
will affect the author of new nodes. Furthermore if you pass an id of 0 pageroute 
will ignore that argument. E.g. you can link to your pageroute by using the path 
"pageroutepath/4/0" to go through the route as the currently logged in user (id 0) 
and with the node id 4 as first argument.

So you can go through the pageroute as another user by appending the user's id to each
URL of the route. E.g. if your pageroute has the path 'example' use 'example/0/1'
to go through the route as user with the uid 1. Of course you need appropriate
permissions if you want to be able to add/edit/delete nodes for other users.
In particular this is useful if you are using pageroute for creating nodeprofiles,
so that administrators can create/edit profiles of other users.


 (*) Using the node display type
 
You can build a pageroute to add/edit nodes, where another page is used for viewing
the resulting node. For this you need the "node edit form" and "node display" page types:
The node edit form page type uses the first argument as node id. The configured 
node id of the node display page type has to be 0, then it will also use the node
id given as argument. So this page will display the node, which has been edited with
the node edit form.
If the node id argument is missing, the node edit form page type will present a node
add form and append the new node id to the next generated path - so the node display
page will show the appropriate node!

 (*) Node management pages & nodefamily

The node management page of a content type obeys the maximum nodefamily population,
if the nodefamily module is installed and activated.
So you may use the nodefamily module to restrict the number of addable nodes for a
content type.

 (*) Nodefamily & Nodeprofiles
 
The nodefamily module provides two further page types. Read the nodefamily README
for more information. They are useful for building nodeprofiles:
http://drupal.org/project/nodeprofile


States Module Integration
-------------------------
The states module isn't released yet, however there is already pageroute integration
available. It will be part of the workflow-ng module package. As long as the workflow-ng
module package isn't released, you can find the states module in my sandbox:

http://cvs.drupal.org/viewcvs/drupal/contributions/sandbox/fago/workflow-ng/

If the states module is installed, there will be a new option for each route, it's called
"Verify that a user goes through each page of the route."

This will be done with the help of the state machine provided by the states module.
This information is used for altering the look of the tab like submit buttons, if activated.
So it will be verfied that a user can only reach the next page in a route.


pageroute_nodefamily.module
---------------------------
Dependencies: Pageroute Module, Nodefamily (http://drupal.org/project/nodefamily)
Suggested: States Module from the Workflow-ng package

This module is still under development, but it provides already some useful functionality.
Currently it might be confusing in particular to unexperienced users, so if you
are unexperienced just ignore this module for now.

Currently this module allows you to associate a pageroute with a content type. Then the 
associated pageroute will be used for editing nodes of this content type. So if this is 
useful for you, you can already use this module for that.

In future this module will create node relations for all nodes created within
the pageroute. This way it will build "nodefamilies", families of nodes. The node of 
the content type associated with the pageroute will be the head of the family, holding
all nodes together. Once created, the nodefamily could be edited with the associated pageroute.
Currently the module doesn't create any node relations!


If the states module is activated, it will be used for tracking the creation state
of the nodefamily. This information is used for altering the look of the tab like
submit buttons, as described above. Furthermore it allows you to determine easily
if the user has gone through the whole pageroute for this nodefamily, so you know
if the nodefamily can be considered complete.

As long as the workflow-ng module package isn't released, you can find the states
module in my sandbox:
http://cvs.drupal.org/viewcvs/drupal/contributions/sandbox/fago/workflow-ng/
