<?php
// $Id: ad_cache_file.inc,v 1.1.4.29 2009/01/29 06:26:03 jeremy Exp $

/**
 * @file
 * A plug in for the ad.module, providing a file cache mechanism for improved
 * performance when displaying ads.
 *
 * TODO: Add support for tracking views/clicks with group-level granularity.
 *
 * Copyright (c) 2007-2008.
 *  Jeremy Andrews <jeremy@kerneltrap.org>.  All rights reserved.
 */

/**
 * This is the actual cache function called by adserve.php that displays ads
 * without bootstrapping Drupal.
 */
function ad_cache_file() {
  static $displayed_count = 0;

  _debug_echo('File cache: entering.');

  $cache_file = ad_cache_file_get_lock();
   
  $output = '';
  if ($cache_file) {
    // Read entire cache file into memory.
    $cache = unserialize(fread(adserve_variable('fd'), filesize($cache_file)));
    // Store cache in a static variable for re-use by other functions.
    ad_cache_file_ro_cache($cache);
    /**
     * The cache structure looks like this:
     * $cache['ad'][$aid]['display'] = $ad
     * $cache['hostid'][$hostid] = TRUE
     * $cache['ad'][$aid][$hostid]['counts'][$action][$timestamp] = $counter
     * $cache['last_sync'] = $timestamp
     */

    /**
     * Initial support for over-riding default functionality when serving ads.
     */
    $includes = array('include_file_init', 'include_file_select');
    foreach ($includes as $include) {
      if (isset($cache[$include])) {
        $include_file = adserve_variable('root_dir') .'/'. $cache[$include];
        if (file_exists($include_file) && is_file($include_file)) {
          _debug_echo("File cache: including external file: '$include_file'.");
          include_once($include_file);
        }
        else {
          _debug_echo("File cache: unable to find external file: '$include_file'.");
        }

        switch ($include) {
          case 'include_file_init':
            $include_func_init = $cache['include_func_init'];
            _debug_echo("File cache: include_func_init: '$include_func_init'.");
            break;
          case 'include_file_select':
            adserve_variable('include_func_select', $cache['include_func_select']);
            _debug_echo("File cache: include_func_select: '". adserve_variable('include_func_select') ."'");
            break;
        }
      }
    }

    $hostid = adserve_variable('hostid') ? adserve_variable('hostid') : 'none';
    _debug_echo("File cache: using hostid: '$hostid'.");
    if ($hostid != 'none' && !isset($cache['hostid'][$hostid])) {
      _debug_echo("File cache: invalid hostid: '$hostid'.");
      $output = 'You do not have permission to display ads.';
    }
    else {
      $last_sync = $cache['last_sync'];
      $lifetime = $cache['lifetime'];
      $time = time();
      $timestamp = date('YmdH');

      // Allow external plug-ins to initialize these values...
      if (function_exists($include_func_init)) {
        $init = $include_func_init($cache, $hostid);
      }
      if (!empty($init)) {
        _debug_echo('File cache: initialized externally.');
        $quantity = $init['quantity'];
        $id = $init['id'];
        $type = $init['type'];
        $aids = explode(',', $id);
        $cache_size = sizeof($aids);
      }
      else {
        $quantity = adserve_variable('quantity');
        if (isset($cache['hostid'][$hostid]['aids'])) {
          $id = $cache['hostid'][$hostid]['aids'];
          $type = 'host';
          $aids = explode(',', $id);
          $cache_size = sizeof($aids);
        }
        else if (adserve_variable('nids')) {
          $id = adserve_variable('nids');
          $type = 'nids';
          $aids = explode(',', $id);
          $cache_size = sizeof($aids);
        }
        else if (adserve_variable('tids')) {
          $id = adserve_variable('tids');
          $type = 'tids';
          if (!isset($cache['tids'][$id])) {
            $cache['tids'][$id] = array();
            $tids = explode(',', $id);
            foreach ($tids as $tid) {
              if (is_array($cache['tid'][$tid]['aid'])) {
                $cache['tids'][$id] += $cache['tid'][$tid]['aid'];
              }
            }
            // Rebuild keys from 0, cache it for re-use on next ad display
            $cache['tids'][$id] = array_values($cache['tids'][$id]);
          }
          $cache_size = sizeof($cache['tids'][$id]);
          $aids = $cache['tids'][$id];
        }
        else {
          $id = 0;
          $type = 'default';
          $cache_size = sizeof($cache['tid'][0]['aid']);
          $aids = $cache['tid'][0]['aid'];
        }
      }
  
      if (adserve_variable('debug')) {
        echo "File cache: last sync: $last_sync<br />\n";
        echo "File cache: current time: $time<br />\n";
        if ($time - $lifetime >= $last_sync) {
          echo "File cache: will rebuild cache now.<br />\n";
        }
        else {
          $seconds = $last_sync - $time + $lifetime;
          echo "File cache: will rebuild cache in $seconds seconds.<br/>\n";
        }
        echo "File cache: timestamp: $timestamp<br />\n";
        echo "File cache: cache_size($cache_size)<br />\n";
      }

      $ids = adserve_variable("$type-ids");
      if ($ids == NULL) {
        $ids = array();
      }
      _debug_echo('File cache: size of $ids: '. sizeof($ids));

      // Only include aids that are in our cache, others are not valid in our
      // context.
      $search = array();
      if (is_array($aids)) {
        foreach ($aids as $aid) {
          if (isset($cache['ad'][$aid])) {
            $search[] = $aid;
          }
        }
      }

      $selected = adserve_select_ad($search, $quantity, $ids);
      adserve_variable("$type-ids", array_merge($selected, $ids));
      foreach ($selected as $aid) {
        $aid = (int)$aid;
        $ad = $cache['ad'][$aid];
  
        if (!empty($output)) {
          // Add a div between ads that themers can use to arrange ads when 
          // displaying more than one at a time.
          $displayed_count++;
          $output .= "<div class=\"advertisement-space\" id=\"$id-$displayed_count\"></div>";
        }
        $output .= $ad['display'];
       
        _debug_echo("File cache: displaying AID: $aid");

        // If displaying an ad, increment appropriate view counter.  Otherwise,
        // simply increment a counter.
        $action = $aid ? 'view' : 'count';
  
        // Increment counter.
        if (isset($cache['ad'][$aid][$hostid]) && 
            isset($cache['ad'][$aid][$hostid]['counts'][$action]) && 
            isset($cache['ad'][$aid][$hostid]['counts'][$action][$timestamp])) {
          $cache['ad'][$aid][$hostid]['counts'][$action][$timestamp]++;
        }
        else {
          $cache['ad'][$aid][$hostid]['counts'][$action][$timestamp] = 1;
        }
      }

      // Write updated cache back to file and release the lock.
      $cache = serialize($cache);
      // Store updated cache in a static variable for re-use by other functions.
      ad_cache_file_ro_cache($cache);
      rewind(adserve_variable('fd'));
      ftruncate(adserve_variable('fd'), 0);
      fwrite(adserve_variable('fd'), $cache, strlen($cache));
      flock(adserve_variable('fd'), LOCK_UN);
      fclose(adserve_variable('fd'));
      adserve_variable('fd', '');
  
      // Every $lifetime seconds we flush the cache files to the database.
      if ($last_sync < time() - $lifetime) {
        ad_cache_file_rebuild();
      }
    }
  }
  else {
    $output = 'Configuration error, failed to lock cache file.';
    if (ad_cache_file_rebuild()) {
      // Required function was missing, the file cache must be disabled, so 
      // return nothing allowing adserve.inc to use the default display method.
      return;
    }
  }
  if (empty($output)) {
    adserve_variable('error', TRUE);
    $output = 'No active ads were found in the '. (empty($nids) ? 'tids' : 'nids') ." '$id'.";
    if (adserve_variable('debug')) {
      echo "$output<br />\n";
    }
  }
  return $output;
}

function ad_cache_file_get_lock() {
  static $lock = FALSE;
  static $cache_file = '';

  if ($lock) {
    _debug_echo('File cache: already have lock.');
    return $cache_file;
  }

  // We'll loop through all possible cache files until we obtain an 
  // exclusive lock.
  for ($i = 1; $i <= adserve_variable('files'); $i++) {
    // Prefix the filename with a '.' to hide it on Unix systems.
    $cache_file = adserve_variable('root_dir') .'/'. adserve_variable('path') .'/.'. $i .'.ad.cache';
  
    if (adserve_variable('debug')) {
      echo "Trying cache_file '$cache_file'.<br />\n";
    }
  
    if (!$fd = @fopen($cache_file, 'r+')) {
      if (adserve_variable('debug')) {
        echo "Failed to open cache_file '$cache_file'.<br />\n";
      }
      // We failed to open the cache file, try the next one.
      continue;
    }
    if ($i < adserve_variable('files')) {
      // This isn't the last available cache file so we'll use a 
      // non-blocking lock for best performance.  If we fail to lock this 
      // cache file, we'll quickly move on to the next until we find an 
      // available one.
      if (!flock($fd, LOCK_EX|LOCK_NB)) {
        if (adserve_variable('debug')) {
          echo "Failed to obtain non-blocking lock.<br />\n";
        }
        // We failed to obtain an exclusive lock, close the file and try the
        // next one.
        @fclose($fd);
        continue;
      }
      if (adserve_variable('debug')) {
        echo "Obtained lock.<br />\n";
        $stat = fstat($fd);
        echo 'File size: '. $stat['size'] .'<br />';
      }
      $lock = TRUE;
      break;
    }
    else {
      // This is the last available cache file, we'll use a blocking lock 
      // as we have to wait until we have exclusive write permissions.
      if (!flock($fd, LOCK_EX)) {
        if (adserve_variable('debug')) {
          echo "Failed to obtain blocking lock.<br />\n";
        }
        // A blocking exclusive lock shouldn't ever fail, so something has
        // gone very wrong.  Perhaps the file was deleted out from under us?
        @fclose($fd);
        continue;
      }
      if (adserve_variable('debug')) {
        echo "Obtained lock on final cache file.<br />\n";
      }
      $lock = TRUE;
      break;
    }
  }
  if ($lock) {
    adserve_variable('fd', $fd);
    return $cache_file;
  }
  else {
    return NULL;
  }
}

function ad_cache_file_increment($action = 'view') {
  _debug_echo("File cache: incrementing '$action'.");
  $cache_file = ad_cache_file_get_lock();
  if ($cache_file) {
    $cache = unserialize(fread(adserve_variable('fd'), filesize($cache_file)));

    $hostid = adserve_variable('hostid') ? adserve_variable('hostid') : 'none';
    $aid = adserve_variable('aid');
    if ($action == 'view') {
      if ($hostid != 'none' && !isset($cache['hostid'][$hostid])) {
        _debug_echo("File cache: invalid hostid: $hostid");
        $output = 'You do not have permission to display images.';
        // TODO: We should still log this.  Perhaps a new $action type?
        return -1;
      }
    }
    $last_sync = $cache['last_sync'];
    $lifetime = $cache['lifetime'];
    $time = time();
    $timestamp = date('YmdH');

    // Increment action counter.
    if (isset($cache['ad'][$aid][$hostid]) && 
        isset($cache['ad'][$aid][$hostid]['counts'][$action]) && 
        isset($cache['ad'][$aid][$hostid]['counts'][$action][$timestamp])) {
      $cache['ad'][$aid][$hostid]['counts'][$action][$timestamp]++;
    }
    else {
      $cache['ad'][$aid][$hostid]['counts'][$action][$timestamp] = 1;
    }
  
    // Write updated cache back to file and release the lock.
    $cache = serialize($cache);
    rewind(adserve_variable('fd'));
    ftruncate(adserve_variable('fd'), 0);
    fwrite(adserve_variable('fd'), $cache, strlen($cache));
    flock(adserve_variable('fd'), LOCK_UN);
    fclose(adserve_variable('fd'));
    adserve_variable('fd', '');

    // Every $lifetime seconds we flush the cache files to the database.
    if ($last_sync < time() - $lifetime) {
      ad_cache_file_rebuild();
    }
    return 1;
  }

  return 0;
}

/**
 *  Additional variables required by the filecache.
 */
function ad_cache_file_variables() {
  // paths are comprised of alphanumerics, underscores, dashes, periods and 
  // slashes.
  $variables = array();
  $variables['path'] = isset($_GET['p']) ? preg_replace('/[^_\-\.\/\\0-9a-zA-Z]/', '', $_GET['p']) : 'files';
  // files is an integer.
  $variables['files'] = isset($_GET['f']) ? (int)$_GET['f'] : 1;
  if ($variables['files'] > 15) {
      echo "Invalid value 'f=". $variables['files'] ."', exiting.<br />\n";
      exit();
  }
  return $variables;
}

/**
 * Bootstrap drupal, then run ad_cache_file_build() from ad.module which will 
 * rebuild all cache files.
 */
function ad_cache_file_rebuild() {
  adserve_bootstrap();
  if (function_exists('ad_cache_file_build')) {
    ad_cache_file_build();
    return 0;
  }
  else {
    return -1;
  }
}

/**
 *
 */
function ad_cache_file_ro_cache($cache = array()) {
  static $ro_cache = array();

  if (!empty($cache)) {
    $ro_cache = $cache;
  }
  return $ro_cache;
}

/**
 *
 */
function ad_cache_file_adserve_select($ads, $invalid) {
  if ($include_func_select = adserve_variable('include_func_select')) {
    _debug_echo("File cache: adserve_select: invoking '$include_func_select()'");
    if (function_exists($include_func_select)) {
      $cache = ad_cache_file_ro_cache();
      if (!empty($cache)) {
        return $include_func_select($ads, $invalid, $cache);
      }
      else {
        _debug_echo("File cache: unexpected error: cache variable empty.");
      }
    }
    else {
      _debug_echo("File cache: adserve_select: '$include_func_select()' not found");
    }
  }
  else {
    _debug_echo("File cache: adserve_select: no select function defined");
  }
}

?>
