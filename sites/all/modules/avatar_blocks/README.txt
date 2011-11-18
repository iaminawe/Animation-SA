DESCRIPTION:

The Avatar Blocks module creates the following blocks: 

  Who's Online Avatars -  a block that displays the user pictures of 
  online users, and optionally a text summary of online users. This 
  block is a visual version of the Who's Online block provided by the 
  core user module.
  
  Who's New Avatars - a block that displays the user pictures of your 
  site's newest members. This block is a visual version of the 
  Who's New block provided by the core user module.

  My Buddylist Avatars - If you have the Buddylist module installed, 
  this block will display the user pictures of the current user's 
  buddies. This block is a visual version of the My Buddylist block 
  provided by the buddylist module.

PREREQUISITES:

In order to use this module, you need to first configure User Pictures. 
From yoursite.com/admin/user/settings, enable the Picture Support 
option. Specify a default picture to use when a user has no picture. 
(You'll need to load the default picture file to your site separately.)
For more information about enabling User Picture support see the post
at http://drupal.org/node/22271.

Individual avatars link to the user profile pages of the avatar owners.
Users will be unable to view these profile pages unless you have enabled
'Access User Profile' on the Access Control page for one or more roles.

INSTALLATION:

Standard drupal module installation instructions apply. Copy the module
folder to your sites/all/modules folder, and then enable the module at
yoursite/admin/build/modules. For more information about installing drupal
modules, see http://drupal.org/node/176044.

OTHER MODULES:

The Avatar Blocks module does not require any other contrib modules to 
work. However, it is significantly more useful when paired with the 
Imagecache module (http://drupal.org/project/imagecache). If the 
Imagecache module is installed, you can select one of the available 
Imagecache presets to apply to each user picture displayed by the 
module.

The My Buddylist block is only available if you have the Buddylist module
(http://drupal.org/project/buddylist) installed and configured.

Browser cacheing issues can be infuriating when working with Imagecache 
and user pictures. The best way around these problems is to install the 
Unique Avatar Module (http://drupal.org/project/unique_avatar).

CREDITS:

In writing this module, I gained great insight from the following sources:

  "Imagecache Example: User Profile Pictures" by Nate Haug
  http://www.lullabot.com/articles/imagecache_example_user_profile_pictures
  
  "PedigreeMusic.com" post on drupal.org by mjmalloy
  http://drupal.org/node/180762

CHANGELOG:

1.0 Initial Release
1.1 Fixes #289733: First Imagecache Preset does not get applied
1.2 Fixes #290760: db_rewrite_sql causes SQL warning

