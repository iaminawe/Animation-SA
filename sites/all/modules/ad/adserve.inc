<?php
// $Id: adserve.inc,v 1.1.2.39 2009/01/29 06:26:02 jeremy Exp $

/**
 * Configuration.
 *
 * By default, adserve configuration happens dynamically as ads are served.
 * However, it is possible to override dynamic settings with static defaults.
 * Refer to the documentation/ADSERVE_CONFIGURATION.txt for details on adding
 * adserve overrides to settings.php.
 *
 * Note that the path to Drupal's root directory can not be overriden in
 * settings.php as adserve needs this path to find settings.php in the first
 * place.  To hard code the path to Drupal's root directory, uncomment the
 * following define statement, and set the correct path.  This is not generally
 * required.
 */
//define('DRUPAL_ROOT', '/var/www/html');

/**
 * The main adserve logic.
 */
function adserve_ad($options = array()) {
  static $displayed_count = 0;

  // If no $options are passed in, assume we're using JavaScript.
  if (!empty($options)) {
    adserve_variable('variable_load', $options);
  }
  else {
    adserve_variable('variable_load');
  }
  adserve_bootstrap(0);

  adserve_debug();

  adserve_variable('error', FALSE);
  $output = NULL;
  if (adserve_variable('adcache') != 'none') {
    /**
     * Ad caches are defined through external modules.  Ad caches are composed 
     * of a module 'ad_cache_TYPE.module' and an include file 
     * 'ad_cache_TYPE.inc' that live in the 'cache/TYPE' subdirectory where 
     * 'TYPE' is replaced with the type of cache.  For example, the included 
     * file cache lives in 'cache/file'.
     *
     * The ad_cache_TYPE.inc file must have a function named ad_cache_TYPE()
     * which is used to display ads.  It can optionally include a function
     * titled ad_cache_TYPE_variables used to extract any necessary
     * variables from the global $_GET array (this can also be used to override
     * values that would normally be set from $_GET).  Any functions used
     * by this code without bootstrapping Drupal should also be in this file.
     *
     * The ad_cache_TYPE.module file should define the drupal _help() hook
     * so the module can be enabled.  It should also define the _adcacheapi()
     * hook allowing for configuration and processing.  Any functions used by
     * this code after bootstrapping Drupal should also be in this module.
     *
     * Refer to cache/file/* for an implementation example.
     */
    $function = 'ad_cache_'. adserve_variable('adcache');
    $output = adserve_invoke_file($function);

  }

  // If there's no output, we assume either there's no cache enabled, or the
  // cache failed.  
  // TODO: Log failures with the watchdog.
  if ($output == NULL) {
    if (adserve_variable('debug')) {
      echo "No cache enabled.<br />\n";
    }
  
    adserve_bootstrap();
    
    if (adserve_variable('nids')) {
      $id = adserve_variable('nids');
      $type = 'nids';
      adserve_variable('group', "n$id");
  
      // Retrieve all active advertisements from the provided nid list.
      $sql = "SELECT aid FROM {ads} WHERE adstatus = 'active' AND aid IN($id)";
      $result = db_query($sql);

      if (adserve_variable('debug')) {
        echo "Searching for ad from nid list: $id.<br />\n";
        echo "Query: \"$sql;\"<br />\n";
      }
    }
    else if (adserve_variable('tids')) {
      $id = adserve_variable('tids');
      $type = 'tids';
      adserve_variable('group', "t$id");

      // Retrieve all active advertisements from the provided tid list.
      $sql = "SELECT a.aid FROM {ads} a INNER JOIN {term_node} n ON a.aid = n.nid WHERE a.adstatus = 'active' AND n.tid IN($id)";
      $result = db_query($sql);

      if (adserve_variable('debug')) {
        echo "Searching for ad from tid list: $id.<br />\n";
        echo "Query: \"$sql;\"<br />\n";
      }
    }
    else {
      $id = 0;
      $type = 'default';
      adserve_variable('group', "$id");

      // Randomly determine which ad to display from those that do not have
      // any tid assigned to them.
      $sql = "SELECT a.aid FROM {ads} a LEFT JOIN {term_node} n ON a.aid = n.nid WHERE a.adstatus = 'active' AND n.tid IS NULL";
      $result = db_query($sql);

      if (adserve_variable('debug')) {
        echo "Searching for ads with no tids.<br />\n";
        echo "Query: \"$sql;\"<br />\n";
      }
    }

    // Build list of all available ads to choose from.
    while ($ad = db_fetch_object($result)) {
      $available[$ad->aid] = $ad->aid;
    }
    if (adserve_variable('debug')) {
      echo 'Available ads: ';
      if (sizeof($ads)) {
        echo implode(', ', $available) ."<br />";
      }
      else {
        echo 'none<br />';
      }
    }

    // Randomly select from available advertisements.
    $selected = adserve_select_ad($available, adserve_variable('quantity'));
      
    $output = '';
    $ads = 0;
    $details = array();
    // Include appropriate module for displaying selected ad.
    foreach ($selected as $aid) {
      $ids[$aid] = $aid;
      $ads++;
      $detail = $details[$aid] = node_load($aid);
      if (!isset($modules[$detail->adtype])) {
        $modules[$detail->adtype] = db_result(db_query("SELECT filename FROM {system} WHERE name = '%s'", "ad_$detail->adtype"));
      }
      if (adserve_variable('debug')) {
        echo 'ad: <pre>';
        print_r($detail);
        echo '</pre>';
        echo "Loading module '". $modules[$detail->adtype] ."'.<br />\n";
      }
      include_once $modules[$detail->adtype];
      
      if ($output) {
        // Add a div between ads that themers can use to arrange ads when 
        // displaying more than one at a time.
        $displayed_count++;
        $output .= "<div class=\"advertisement-space\" id=\"space-$id-$displayed_count\"></div>";
      }
      $output .= module_invoke("ad_$detail->adtype", 'display_ad', $detail);

      // Update the ad's view counter.
      if (adserve_variable('ad_display') == 'raw') {
        $output .= ad_display_image($detail);
      }
      else {
        adserve_increment($detail);
      }
    }
    adserve_variable("$type-ids", $ids);
    if (empty($ads)) {
      adserve_variable('error', TRUE);
      $output = 'No active ads were found in the '. (empty($nids) ? 'tids' : 'nids') ." '$id'.";
      adserve_increment(NULL, 'count');
    }
    if (adserve_variable('debug')) {
      echo "Ads displayed: $ads<br />";
    }
  }

  $hostid = adserve_variable('hostid');
  $group = adserve_variable('group');
  if ($url = htmlentities(adserve_variable('url'))) {
    $replace = "/$group/$hostid?u=$url";
  }
  else {
    $replace = "/$group/$hostid";
  }

  $output = preg_replace('&/@HOSTID___&', $replace, $output);
  if (adserve_variable('error')) {
    $output = "<!-- $output -->";
  }

  /**
   * Modules can add custom code to be displayed before or after ads are
   * displayed.  For example, you many want to add a tagline, "Powered by 
   * Drupal".  To do so, define 'adserve_exit_text' within your module's
   * adapi hook.
   *
   * Code sample for adserve_exit_text example:
   *
   *   sample_adapi($op, $ad) {
   *     case 'adserve_exit_text':
   *       return array(
   *         'sample' => array(
   *           'text' => t('Powered by Drupal'),
   *         )
   *       );
   *   }
   *
   * As another example use case, you could also use the _init_text and 
   * _exit_text hooks to wrap all advertisements in a custom div.
   */
  $init = TRUE;
  foreach (array('adserve_init_text', 'adserve_exit_text') as $hook) {
    $result = adserve_invoke_hook($hook);
    if (is_array($result)) {
      $append = '';
      foreach ($result as $text) {
        if ($text['text']) {
          $append .= $text['text'];
        }
      }
      if ($init) {
        $output = $append . $output;
      }
      else {
        $output .= $append;
      }
    }
    $init = FALSE;
  }

  switch (adserve_variable('ad_display')) {
    case 'iframe':
    case 'jquery':
      if (!adserve_variable('debug')) {
        // Tell the web browser not to cache this frame so the ad refreshes 
        // each time the page is viewed.

        // Expires in the past:
        header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
        // Last load:
        header('Last-Modified: '. gmdate('D, d M Y H:i:s') .' GMT');
        // HTTP 1.1:
        header('Cache-Control: no-store, no-cache, must-revalidate');
        header('Cache-Control: post-check=0, pre-check=0', false);
        // HTTP 1.0:
        header('Pragma: no-cache');
      }
      print "$output";
      exit(0);
    case 'javascript':
    default:
      $output = str_replace(array("\r", "\n", "<", ">", "&"),
                            array('\r', '\n', '\x3c', '\x3e', '\x26'),
                            addslashes($output));
      if (!adserve_variable('debug')) {
        // Tell the web browser not to cache this script so the ad refreshes 
        // each time the page is viewed.
        // Expires in the past:
        header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
        // Last load:
        header('Last-Modified: '. gmdate('D, d M Y H:i:s') .' GMT');
        // HTTP 1.1:
        header('Cache-Control: no-store, no-cache, must-revalidate');
        header('Cache-Control: post-check=0, pre-check=0', false);
        // HTTP 1.0:
        header('Pragma: no-cache');
        // Output is a JavaScript:
        header('Content-Type: application/x-javascript; charset=utf-8');
      }
      print "document.write('$output');";
      exit(0);
    case 'raw':
      chdir(adserve_variable('ad_dir'));
      return $output;
  }
}

/**
 * Retrieve variables from $_GET array or from passed in $value array.
 */
function adserve_variable($variable, $value = NULL) {
  global $conf;
  static $variables = NULL, $overridden = NULL, $cache_loaded = array();

  // Update the value, if set.
  if (isset($value)) {
    $variables->$variable = $value;
  }

  $loaded = FALSE;
  if (!isset($variables->loaded) || $variable == 'variable_load') {
    if ($variable == 'variable_load' && isset($value)) {
      $values['debug'] = $value['debug'];
      $values['c'] = $value['adcache'];
      $values['n'] = $value['nids'];
      $values['t'] = $value['tids'];
      $values['k'] = $value['hostid'];
      $values['q'] = $value['quantity'];
      $values['m'] = $value['ad_display'];
      unset($value);
    }
    else {
      $values = $_GET;
    }

    // Don't use getcwd as path may involve symbolic links
    $variables->ad_dir = dirname($_SERVER['SCRIPT_FILENAME']);
    // 'debug' is an integer.
    $variables->debug = isset($values['debug']) ? (int)$values['debug'] : 0;
    // Cache types are comprised of only letters.
    $variables->adcache = isset($values['c']) ? preg_replace('/[^a-zA-Z]/', '', $values['c']) : 'none';
    // Nids is an integer or a ",".
    $variables->nids = isset($values['n']) ? preg_replace('/[^0-9,]/', '', $values['n']) : '';
    // Tids is an integer or a ",".
    $variables->tids = isset($values['t']) ? preg_replace('/[^0-9,]/', '', $values['t']) : '';
    // Hostid is an md5() which is comprised of numbers and letters a-f.
    $variables->hostid = isset($values['k']) ? preg_replace('/[^0-9a-f]/', '', $values['k']) : '';
    // Click url
    $variables->url = isset($values['u']) ? $values['u'] : '';
    // Quantity is an integer.
    $variables->quantity = isset($values['q']) ? (int)$values['q'] : 0;
    // Ad ID is an integer.
    $variables->aid = isset($values['a']) ? (int)$values['a'] : 0;
    // Method is compriese of only letters.
    $variables->ad_display = isset($values['m']) ? preg_replace('/[^a-zA-Z]/', '', $values['m']) : 'javascript';

    // Set defaults.
    $variables->quantity = $variables->quantity ? $variables->quantity : 1;

    if ($variables->debug) {
      foreach ($variables as $variable => $val) {
        echo "$variable: '$val'<br />\n";
      }
      if ($variables->debug == 1) exit;
    }
    $variables->loaded = TRUE;

    // Override the value, if set during initialization.
    if (isset($value)) {
      $variables->$variable = $value;
    }
    $loaded = TRUE;
  }

  if (!$overridden) {
    if (isset($conf)) {
      foreach ($conf as $var => $val) {
        $variables->$var = $val;
        if ($variables->debug) {
          echo "Override $var: '$val'<br />\n";
        }
      }
      $overridden = TRUE;
    }
  }

  if (!isset($cache_loaded[$variables->adcache])) {
    // Retrieve variables defined by cache plugin, if enabled.
    if ($variables->adcache != 'none') {
      $include = $variables->ad_dir ."/cache/$variables->adcache/ad_cache_$variables->adcache.inc";
      if (file_exists($include)) {
        if ($variables->debug) {
          echo "Attempting to include cache include file '$include'.<br />\n";
        }
        require_once ($include);
      }
      else if ($variables->debug) {
        echo "Failed to find cache include file '$include'.<br />\n";
      }
      $function = "ad_cache_$variables->adcache". '_variables';
      if (function_exists($function)) {
        $external_variables = $function();
        foreach ($external_variables as $key => $val) {
          if (!isset($variables->$key)) {
            $variables->$key = $val;
          }
        }
      }
    }
    $cache_loaded[$variables->adcache] = TRUE;
  }

  if ($variable == 'variable_dump') {
    echo "Dumping \$variables:<br />\n";
    echo '<pre>';
    foreach ($variables as $var => $val) {
      echo "  $var($val)<br />\n";
    }
    echo '</pre>';
  }

  if (isset($variables->$variable)) {
    return $variables->$variable;
  } 
  else {
    return NULL;
  }
}

/**
 * Invoke a function in the specified file.
 */
function adserve_invoke_file($function, $arg1 = NULL, $arg2 = NULL) {
  $output = '';
  if (function_exists($function)) {
    $output = $function($arg1, $arg2);
  }
  else if (adserve_variable('debug')) {
    echo "Function '$function' does not exist.<br />\n";
  }
  return $output;
}

/**
 * Invoke adserve hooks, defined in adapi with adserve_HOOK.
 */
function adserve_invoke_hook($hook, $a1 = NULL, $a2 = NULL) {
  if (adserve_variable('adcache') != 'none') {
    $cache = adserve_variable('adcache');
    _debug_echo("Invoking adserve hook '$hook' in $cache cache.");
    // Get information from cache.
    return adserve_invoke_file("ad_cache_{$cache}_$hook", $a1, $a2);
  }
  else {
    _debug_echo("Invoking adserve hook '$hook'.");
    // Get information from Drupal variable table.
    $actions = variable_get($hook, '');
    $return = array();
    if (!empty($actions)) {
      $actions = unserialize($actions);
      foreach ($actions as $name => $action) {
        if ($action['function']) {
          $function = $action['function'];
          if (!function_exists($function)) {
            if ($action['path']) {
              _debug_echo("Including file '". $action['path'] ."'.");
              include_once($action['path']);
            }
          }
          if (function_exists($function)) {
            _debug_echo("Invoking function '$function'.");
            $return[] = $function($a1, $a2);
          }
          else if (adserve_variable('debug')) {
            echo "Function '$function' does not exist.<br />\n";
          }
        }
        else {
          $return[] = $action;
        }
      }
    }
    return $return;
  }
  // Retreive hook definition from cache if using, or from variable_get
  // return hook action.
}

function _debug_echo($text) {
  if (adserve_variable('debug')) {
    echo "$text<br />\n";
  }
}

/**
 * Remove one or more ids from array.
 * TODO: Optimize.  Perhaps something like array_flip, unset, array_flip.
 * @param $ids An array of ID's, ie array(5, 8, 9, 11).
 * @param $remove An ID or an array of ID's to be removed from $ids.
 */
function adserve_select_reindex($ids, $remove) {
  $new = array();
  // Walk through array of IDs and decide what to keep.
  foreach ($ids as $id) {
    // If $remove is an array, walk through array to decide fate of ID.
    if (is_array($remove)) {
      $keep = TRUE;
      foreach ($remove as $rem) {
        // Loop until we find one that matches or reach end of array.
        if ($id == $rem) {
          $keep = FALSE;
          break;
        }
      }
      if ($keep) {
        $new[] = $id;
      }
    }
    else {
      if ($id != $remove) {
        $new[] = $id;
      }
    }
  }
  return $new;
}

/**
 * Disabled: will be re-implemented with new adserve hooks introduced for
 * geotargeting.
function adserve_invoke_weight($ads, $quantity = 1, $invalid = array()) {
  $parent = adserve_variable('ad_dir') .'/weight';
  if (is_dir($parent) && $handle = opendir($parent)) {
    while ($dir = readdir($handle)) {
      if (is_dir("$parent/$dir") && !in_array($dir, array('.', '..', 'CVS'))) {
        $include = "$parent/$dir/ad_weight_$dir.inc";
        if (file_exists($include)) {
          require_once($include);
          $function = "ad_weight_{$dir}_select_ad";
          if (function_exists($function)) {
            $return = $function($ads, $quantity, $invalid);
            // First come, first serve.  We found an ad_weight function that
            // returned something, so we'll take it.
            if ($return) {
              return $return;
            }
          }
        }
      }
    }
  }
}
 */

/**
 * Simple default function to randomly select an ad.  Provides a hook to allow 
 * the definition of external display methods.
 * @param An array of valid ad IDs, ie array(5, 8, 9, 11).
 * @param Optional, how many unique ads to select.
 * @param Optional, an array of invalid IDs.
 */
function adserve_select_ad($ads, $quantity = 1, $invalid = array()) {
  //adserve_invoke_weight($ads, $quantity, $invalid);

  $ids = array();
  $id = 0;
  $total = sizeof($ads);
  _debug_echo("Selecting $quantity ad(s) from $total total ad(s).");
  if (is_array($ads)) {
    $ads = adserve_select_reindex($ads, $invalid);
    $total = sizeof($ads);
    for ($i = 0; $i < $quantity; $i++) {
      _debug_echo('Randomly selecting ad: '. ($i + 1) ." of $quantity.");
      $id = 0;
      // Randomly select a unique banner to display.  We subtract 1 as arrays
      // start at 0.
      $return = adserve_invoke_hook('adserve_select', $ads, $invalid);
      if (is_array($return) && !empty($return)) {
        foreach ($return as $id) {
          // First come first serve.
          if ((int)$id) break;
        }
      }
      if ($id == 0) {
        _debug_echo("Default ID selection in adserve.inc.");
        $id = $total > 1 ? $ads[mt_rand(0, $total - 1)] : $ads[0];
        _debug_echo("Randomly selected ID: $id.");
      }
      if ($id > 0) {
        $ids[] = $id;
      }
      else if ($id < 0) {
        // There are no more valid advertisements left to display.
        break;
      }
      $invalid[] = $id;
      $ads = adserve_select_reindex($ads, $id);
      $total = sizeof($ads);
      // We're out of ads to display.
      if ($total <= 0) {
        break;
      }
    }
  }
  return $ids;
}

/**
 * Include Drupal's bootstrap.inc.
 */
function adserve_include_drupal() {
  // For optimal performance set DRUPAL_ROOT at the top of this file.
  if (defined('DRUPAL_ROOT')) {
    if (is_dir(DRUPAL_ROOT) && file_exists(DRUPAL_ROOT .'/includes/bootstrap.inc')) {
      chdir(DRUPAL_ROOT);
    }
    else {
      echo 'Invalid DRUPAL_ROOT ('. DRUPAL_ROOT .') defined in adserve.inc';
    }
  }
  else {
    $path = explode('/', adserve_variable('ad_dir'));
    while (!empty($path)) {
      // Search for top level Drupal directory to perform bootstrap.
      chdir(implode('/', $path));
      if (file_exists('./includes/bootstrap.inc')) {
        break;
      }
      array_pop($path);
    }
  }
  adserve_variable('root_dir', getcwd());
  require_once adserve_variable('root_dir') .'/includes/bootstrap.inc';
}

/**
 * Include the necessary files and call the Drupal bootstrap.
 */
function adserve_bootstrap($bootstrap = NULL) {
  adserve_include_drupal();

  // If no specific bootstrap is specified, do a full bootstrap.
  if (!isset($bootstrap)) {
    $bootstrap = DRUPAL_BOOTSTRAP_FULL;
  }

  if (adserve_variable('debug')) {
    echo "Drupal bootstrap '". $bootstrap ."'.<br />\n";
  }

  drupal_bootstrap($bootstrap);
}

/**
 * Increment ad counters.  Increment in cache if enabled.
 */
function adserve_increment($ad, $action = 'view') {
  $cache = adserve_variable('adcache');
  if (adserve_variable('debug')) {
    echo "adserve_increment action($action) cache($cache)<br />\n";
  }
  if ($cache != 'none') {
    $rc = adserve_invoke_file("ad_cache_{$cache}_increment", $action);
    if ($rc) return;
  }
  adserve_bootstrap();
  // Update view statistics.
  db_query("UPDATE {ad_statistics} SET count = count + 1 WHERE aid = %d AND action = '%s' AND date = %d AND adgroup = '%s' AND hostid = '%s'", $ad->aid, $action, date('YmdH'), adserve_variable('group'), adserve_variable('hostid'));
  // If column doesn't already exist, we need to add it.
  if (!db_affected_rows()) {
    db_query("INSERT INTO {ad_statistics} (aid, date, action, adgroup, hostid, count) VALUES(%d, %d, '%s', '%s', '%s', 1)", $ad->aid, date('YmdH'), $action, adserve_variable('hostid'), adserve_variable('hostid'));
    // If another process already added this row our INSERT will fail, if 
    // so we still need to increment it so we don't loose a view.
    if (!db_affected_rows()) {
      db_query("UPDATE {ad_statistics} SET count = count + 1 WHERE aid = %d AND action = '%s' AND date = %d AND adgroup = '%s' AND hostid = '%s'", $ad->aid, $action, date('YmdH'), adserve_variable('group'), adserve_variable('hostid'));
    }
  }
  
  if ($action == 'view') {
    // See if we need to perform additional queries.
    if ($ad->maxviews) {
      $views = (int)db_result(db_query("SELECT SUM(count) FROM {ad_statistics} WHERE aid = %d AND action = 'view' AND date >= %d", $ad->aid, date('YmdH', $ad->activated)));
      if ($views >= $ad->maxviews) {
        db_query("UPDATE {ads} SET adstatus = 'expired', autoexpire = 0, autoexpired = %d, expired = %d WHERE aid = %d", time(), time(), $ad->aid);
        ad_statistics_increment($ad->aid, 'autoexpired');
        ad_statistics_increment($ad->aid, 'expired');
      }
    }
  }
  // TODO: Do we need to do this here?  Can it happen when a new click is
  // registered?
  if ($ad->maxclicks) {
    $clicks = (int)db_result(db_query("SELECT SUM(count) FROM {ad_statistics} WHERE aid = %d AND action = 'click' AND date >= %d", $ad->aid, date('YmdH', $ad->activated)));
    if ($clicks >= $ad->maxclicks) {
      db_query("UPDATE {ads} SET adstatus = 'expired', autoexpire = 0, autoexpired = %d, expired = %d WHERE aid = %d", time(), time(), $ad->aid);
      ad_statistics_increment($ad->aid, 'autoexpired');
      ad_statistics_increment($ad->aid, 'expired');
    }
  }
}

/**
 * Display additional debug information.
 */
function adserve_debug() {
  if (adserve_variable('debug')) {
    echo "Root drupal directory detected as '". adserve_variable('root_dir') ."'.<br />\n<br />\n";

    $ad_dir = adserve_variable('ad_dir');
    $files = array("$ad_dir/serve.php", "$ad_dir/ad.module");
    if (adserve_variable('debug') > 2) {
      $files = array_merge($files, array("$ad_dir/ad.install", "$ad_dir/ad_views.inc"));
    }
    if (adserve_variable('debug') > 3) {
      $files = array_merge($files, array("$ad_dir/image/ad_image.module", "$ad_dir/image/ad_image.install", "$ad_dir/image/ad_image_views.inc", "$ad_dir/text/ad_text.module", "$ad_dir/text/ad_text.install", "$ad_dir/text/ad_text_views.inc", "$ad_dir/embed/ad_embed.module", "$ad_dir/report/ad_report.module", "$ad_dir/notify/ad_notify.module", "$ad_dir/notify/ad_notify.install"));
    }
    foreach ($files as $file) {
      if (!file_exists($file)) {
        echo "Error: '$file' does not exist!<br />\n";
      }
      else if (!is_readable($file)) {
        echo "Error: '$file' is not readable!<br />\n";
      }
      else {
        $fd = fopen($file, 'r');
        while (!feof($fd)) {
          $line = fgets($fd);
          if (substr($line, 0, 5) == "<?php") {
            continue;
          }
          else {
            echo "$file: $line<br />";
            break;
          }
        }
      }
    }
    echo "<br />\n";
  }
}

