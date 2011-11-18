Drupal service_links module:
------------------------
Author - Fredrik Jonsson fredrik at combonet dot se
Mantainer - Fabio Mucciante aka TheCrow
Requires - Drupal 5
License - GPL (see LICENSE)


Overview:
--------
The service links module enables admins to add the following
links to nodes:
* Buzz - Buzz up this post on Yahoo! Buzz
* del.icio.us - Bookmark this post on del.icio.us
* Digg - Submit this post on digg.com
* Facebook - Submit this URL on Facebook
* Furl - Submit this post on Furl
* Google - Bookmark this post on Google
* IceRocket - Search IceRocket for links to this post
* LinkedIn - Add this post on LinkedIn
* ma.gnolia.com - Bookmark this post on ma.gnolia.com
* Newsvine - Submit this post on Newsvine
* PubSub - Search PubSub for links to this post
* Reddit - Submit this post on reddit.com
* StumbleUpon - Bookmark this post on StumbleUpon
* Technorati - Search Technorati for links to this post
* Twitter - Submit this post on Twitter
* Yahoo - Bookmark this post on Yahoo

The site owner can deside:
- To show the links as text, image or both.
- What node types to display links for.
- If the links should be displays in teaser view or full page view
  or both.
- If the links should be added after the body text or in the links
  section or in a block.
- If aggregator2 nodes should use link to original article aggregated
  by aggregator2 module.
- Deside what roles get to see/use the service links.


Installation and configuration:
------------------------------
Copy the whole 'service_links' folder
under your 'modules' directory and then 
enable the module at 'administer >> modules'.
Go to 'administer >> access control' for allow
users to watch the links.

For configuration options go to 'administer >> settings
>> service_links'.


Add links to new services:
-------------------------
Open the file service_links.module in your text editor and in the
function service_links_render() you will find this comment
at the end.

// Add your own link by modifing the link below and uncomment it.
//$links[] = theme('service_links_build_link', t('delicious'), "http://del.icio.us/post?url=$url&title=$title", t('Bookmark this post on del.icio.us.'), 'delicious.png');


Include service links in your theme:
-----------------------------------
In the included template.php file there  an example how to insert
the service links in to a PHPTemplate theme. Remember to place the
template.php file in the folder of your theme or integrate it with 
the content of 'template.php' provided from your theme.


Last updated:
------------
$Id: README.txt,v 1.9.2.2 2009/03/20 10:39:31 thecrow Exp $
