/* $Id: avatar_selection_pager.js,v 1.1.4.5 2009/06/07 23:34:30 snpower Exp $ */

/**
 * Fetches the new page and puts it inline.
 *
 * @param form_id   - The id of the form whose action should be updated.
 * @param id   - The element id whose contents will get replaced.
 * @param url - The URL for the new page.
 * @param page  - The page number to request.
 * @param js_file  - The javascript file to run upon completion.
 */
function fetchPage(form_id, id, url, page, js_file) {
  $("body").css({'opacity': 0.5});
  $("#avatar-selection-loading").show();
  $.get(url, {page: page}, function(data, status) {
    var selects = $(data).find(id);
    $(id).html(selects);
    var pager = $(data).find(".avatar-selection-pager-nav");
    $(".avatar-selection-pager-nav").html(pager);
    $.getScript(js_file);
    var action = url + "?page="+page;
    $(form_id).attr("action", action);
    $("#avatar-selection-loading").hide();
    $("body").css({'opacity': null});
  });
  return false;
}
