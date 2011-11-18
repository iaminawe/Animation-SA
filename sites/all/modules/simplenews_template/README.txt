// $Id: README.txt,v 1.3.4.5 2009/02/02 22:21:14 tbarregren Exp $


Simplenews Template
===================

Simplenews Template is a Drupal module that extends the Simplenews module by
providing a themable template with configurable header, footer and style.
Header, footer and style are configurable for each newsletter independently.

Simplenews Template can with advantage be used in conjunction with
RelatedContent <http://drupal.org/project/relatedcontent>.

Developed by

  * Thomas Barregren <http://drupal.org/user/16678>

Sponsored by

  * Spoon Media <http://www.spoon.com.au/>
  * NodeOne <http://www.nodeone.se/>


Requirements
------------

To install Simplenews Template you need:

  * Drupal 5.x
  * Simplenews
  * Mime Mail
  * PHPTemplate based theme


Installation
------------

Install Simplenews Template as follows:

  1. Download, install and configure the Mime Mail module.
     See http://drupal.org/project/mimemail.

  2. Download, install and configure the Simplenews module.
     See http://drupal.org/project/simplenews.

  3. Download the latest stable version of Simplenews Template.
     See http://drupal.org/project/simplenews_template.

  4. Unpack the downloaded file into sites/all/modules or the modules directory
     of your site.

  5. Go to Administer » Site building » Modules and enable the module.
  
  6. OPTIONAL: To enable automatic insertion of the Simplenews Template style
     definitions into HTML-tags of e-mails, download the Emogrifier from
     http://www.pelagodesign.com/sidecar/emogrifier/ and extract the file
     emogrifier.php file into the Simplenews Template folder. More information
     below.


Configuration
-------------

There is no configuration for the Simplenews Template module itself.


Usage
-----

Header, footer and style is setup for each newsletter individually as follows:

  1. If not already existing, go to admin/content/newsletters/types and add at
     least one newsletter.

  2. Go to admin/content/newsletters/settings, and select the newsletter to be
     configured.

  3. Open the collapsible section called "Header".
  
     3.1 Check the box "Include header in nodes?" to include the header when
         viewing nodes with issues of the newsletter. The header is always
         included in e-mails with issues of the newsletter.
     
     3.2 Fill out the text area "Header" with the content to be shown at the
         beginning of each issue of the newsletter. Leave blank to not include
         a header. Do not forget to choose an appropriate input format.

  4. Open the collapsible section called "Footer".
  
     4.1 Check the box "Include footer in nodes?" to include the footer when
         viewing nodes with issues of the newsletter. The footer is always
         included in e-mails with issues of the newsletter.
     
     4.2 Fill out the text area "Footer" with the content to be shown at the
         end of each issue of the newsletter. Leave blank to not include
         a footer. Do not forget to choose an appropriate input format.

  5. Open the collapsible section called "Style".
  
     5.1 Check the box "Include CSS in nodes?" to include the CSS rules when
         viewing nodes with issues of the newsletter. The CSS rules are always
         included in e-mails with issues of the newsletter.
     
     5.2 Fill out the text area called "CSS" with CSS rules, e.g.
         `div.message { color: red }`.
     
     5.3 Fill out the text field called "Body background color" with the HTML
         color value, e.g. Yellow or #ffff00, to use in the bgcolor attribute
         of the <body> element.


Theming
-------

The included simplenews_template.tpl.php file is the default template for
the HTML e-mails. DON'T EDIT IT!

If you want to make changes to simplenews_template.tpl.php, copy it to the
current theme's directory, and make your modification to that file. See
simplenews_template.tpl.php for more information.

If you want a particular newsletter to have an own template, copy
simplenews_template.tpl.php to simplenews_template-xxx.tpl.php, where xxx
is the identity number of the newsletter, and move it to the current theme's
directory. You find the newsletters identity number at the end of the URL
to its settings page, e.g. the page with the header, footer and style fields.


Emogrifier
----------

Some e-mail clients, notably Microsoft Outlook 2007 and Google Gmail, discharge
CSS defintions within <style> tags. The solution is to put the style
definitions into the e-mail HTML-tags. Simplenews Template can do this
automagically if Emogrifier <http://www.pelagodesign.com/sidecar/emogrifier/>
is installed as described above.

Emogrifier supports not all CSS2 selectors, e.g. pseudo selectors. All CSS1
selectors works.

Emogrifier parses the CSS selectors in order. Later selectors will therefore
override earlier selectors that apply to the same element.

Notice that even with Emogrifier certain e-mail clients will ignore certain
CSS properties. For more information, see http://www.email-standards.org/.
