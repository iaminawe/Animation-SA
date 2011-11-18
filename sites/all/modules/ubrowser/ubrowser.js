// $Id$

// Used to return the uBrowser div to normal if it's closed.
var oldcontents = null;

// Used to keep from performing the same search twice in a row.
var lastsearch = '';

/**
 * Load uBrowser into the div specified by selector..
 */
function display_ubrowser(basepath, settings) {
  if (oldcontents == null) {
    oldcontents = $(settings['div']).html();
  }

  $.post(basepath + '?q=ubrowser/main', settings,
         function(contents) {
           $(settings['div']).empty().addClass(settings['class']).append(contents);
         }
  );

  return false;
}

/**
 * Load the uBrowser based on the builder.
 */
function build_ubrowser(basepath, code_id) {
  var filter = '';
  $('#filter-checkboxes .form-checkbox').each(
    function() {
      if (this.checked) {
        if (filter == '') {
          filter = this.id.substring(16);
        }
        else {
          filter += ',' + this.id.substring(16);
        }
      }
    }
  );

  var settings = {
    'div'    : $('#edit-ubb-div').val(),
    'class'  : $('#edit-ubb-class').val(),
    'vid'    : $('#edit-ubb-vid').val(),
    'nids'   : ($('#edit-ubb-nids:checked').val() !== null) ? 'true' : 'false',
    'search' : ($('#edit-ubb-search:checked').val() !== null) ? 'true' : 'false',
    'view'   : ($('#edit-ubb-view:checked').val() !== null) ? 'true' : 'false',
    'window' : ($('#edit-ubb-window:checked').val() !== null) ? 'new' : 'current',
    'close'  : ($('#edit-ubb-close:checked').val() !== null) ? 'true' : 'false',
    'multi'  : ($('#edit-ubb-multi:checked').val() !== null) ? 'true' : 'false',
    'categ'  : $('#edit-ubb-categ').val(),
    'nodesg'  : $('#edit-ubb-nodesg').val(),
    'nodepl'  : $('#edit-ubb-nodepl').val(),
    'filter' : filter,
    'select' : $('#edit-ubb-select').val()
  }

  display_ubrowser(basepath, settings);

  // Create the code output for admin/content/browse.
  if (code_id != null) {
    var output = "<?php\n\n$settings = array(\n";
    output += "  'div' => '" + settings['div'] + "',\n";
    output += "  'class' => '" + settings['class'] + "',\n";
    output += "  'vid' => " + settings['vid'] + ",\n";
    output += "  'nids' => '" + settings['nids'] + "',\n";
    output += "  'search' => '" + settings['search'] + "',\n";
    output += "  'view' => '" + settings['view'] + "',\n";
    output += "  'window' => '" + settings['window'] + "',\n";
    output += "  'close' => '" + settings['close'] + "',\n";
    output += "  'multi' => '" + settings['multi'] + "',\n";
    output += "  'categ' => '" + settings['categ'] + "',\n";
    output += "  'nodesg' => '" + settings['nodesg'] + "',\n";
    output += "  'nodepl' => '" + settings['nodepl'] + "',\n";
    output += "  'filter' => '" + settings['filter'] + "',\n";
    output += "  'select' => \"" + settings['select'] + "\",\n";
    output += ");\n\nprint ubrowser($settings, '" + settings['div'].replace(/#/, '') + "');\n\n?>"

    $(code_id).html(output);
  }

  return false;
}

/**
 * Load the node select box when you click on a category term.
 */
function load_node_select(tid, basepath) {
  if (parseInt(tid) < 0) {
    return false;
  }

  lastsearch = '';
  var settings = {
    'multi'  : $('#edit-ub-multi').val(),
    'filter' : $('#edit-ub-filter').val(),
    'categ'  : $('#edit-ub-categ').val(),
    'nodesg' : $('#edit-ub-nodesg').val(),
    'nodepl' : $('#edit-ub-nodepl').val()
  };

  $.post(basepath + '?q=ubrowser/nodes/' + tid + $('#edit-ub-nids').val(), settings,
         function(contents) {
           $('#ubrowser-nodes').empty().append(contents);
           $('#edit-unid').dblclick( function () { ubrowser_action_select(); } );
         }
  );
}

/**
 * Execute the search without browsing away on accident.
 */
function ubrowser_search_submit() {
  $('#usearch_submit').click();

  return false;
}

/**
 * Load the node select box with the search results when you click Search.
 */
function load_node_search(basepath) {
  var settings = {
    'keys'   : $('#edit-usearch-keys').val(),
    'nids'   : $('#edit-ub-nids').val(),
    'filter' : $('#edit-ub-filter').val(),
    'categ'  : $('#edit-ub-categ').val(),
    'nodesg' : $('#edit-ub-nodesg').val(),
    'nodepl' : $('#edit-ub-nodepl').val()
  };

  // Don't update the search if the search keys haven't changed since last time.
  if (settings['keys'] == lastsearch) {
    return false;
  }
  lastsearch = settings['keys'];

  $.post(basepath + '?q=ubrowser/nodesearch', settings,
         function(contents) {
           if (contents != '') {
             $('#ubrowser-nodes').empty().append(contents);
             $('#edit-unid').dblclick( function () { ubrowser_action_select(); } );
           }
         }
  );

  return false;
}

/**
 * Browse to the selected node when the view button is clicked.
 */
function ubrowser_action_view(basepath) {
  // Don't go if they haven't selected an actual node yet.
  var nid = $('#edit-unid').val();
  if (parseInt(nid) > 0) {
    var url = basepath + '?q=' + $('#edit-unid-path-' + nid).val();
    if ($('#edit-ub-window').val() == 'new') {
      window.open(url);
    }
    else {
      window.location = url;
    }
  }

  return false;
}

/**
 * Execute the Javascript defined for the select button.
 */
function ubrowser_action_select() {
  eval($('#edit-ub-select').val());

  return false;
}

/**
 * Close the uBrowser, emptying it and removing its class.
 */
function ubrowser_action_close() {
  var ub_div = $('#edit-ub-div').val();
  var ub_class = $('#edit-ub-class').val();

  $(ub_div).empty().html(oldcontents);
  
  if (ub_class !== '') {
    $(ub_div).removeClass(ub_class);
  }

  return false;
}
