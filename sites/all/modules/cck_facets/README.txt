$Id: README.txt,v 1.8 2008/04/23 14:58:40 davidlesieur Exp $

README file for the CCK Facets Drupal module package.


Description
***********

CCK Facets is a bundle of modules that integrate with Faceted Search to expose
Content Construction Kit (CCK) fields as facets. This allows users to browse
field values and to filter search results with those values.

The supported CCK field types are:

- Text
- Number
- Node Reference
- User Reference
- Date
- Datestamp


Requirements
************

- Drupal 5.x (http://drupal.org/project/drupal).

- Faceted Search (http://drupal.org/project/faceted_search).

- Content Construction Kit (CCK) (http://drupal.org/project/cck).


Installation
************

1. Extract the cck_facets package directory into your Drupal modules directory.

2. Go to the Administer > Site building > Modules page, and enable the CCK
   Facets module.

3. Enable any of the following modules, depending on the types of CCK fields you
   wish to expose as facets:

   - CCK Text Facets (for Text fields)
   - CCK Number Facets (for Number fields)
   - CCK Reference Facets (for Node Reference or User Reference fields)
   - CCK Date Facets (for Date or Datestamp fields)

   Only the above types of fields are supported at the moment.

4. Go to the Administer > Site configuration > Faceted Search page, edit the
   faceted search environment that shall expose CCK-based facets. In the
   environment editing form, check each facet you wish to expose.

   CAUTION: This system hands you over the responsibility of deciding what field
   is appropriate for use as a facet. Long text fields should never be used as
   facets, since their values are too long to be usable in the Guided search,
   and might exceed the maximum URL length in browsers or servers when used as
   search criteria.


Support
*******

For support requests, bug reports, and feature requests, please use the
project's issue queue on http://drupal.org/project/issues/cck_facets.

Please DO NOT send bug reports through e-mail or personal contact forms, use the
aforementioned issue queue instead.


Credits
*******

- Sponsored by Laboratoire NT2 (http://www.labo-nt2.uqam.ca).

