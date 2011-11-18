// $Id $
// Author: Mark Burton


if (Drupal.jsEnabled) {
  $(document).ready(
    function() {
      //the 'select from select box' has been selected
      
      $('select.taxonomySearch_tids').change(
        function() {
          fieldid=this.id;
          tids=$('.taxonomySearch_tids').filter('[@id*='+fieldid+']').val();
          $('.taxonomySearch_nids').filter('[@id*='+fieldid+']').removeOption(/./).ajaxAddOption("/taxonomySearch/autocomplete/"+fieldid+"/"+tids);
        });
      
    });
  
}
