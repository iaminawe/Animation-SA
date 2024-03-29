<?php
// $Id: video_filter.codecs.inc,v 1.1.2.8.2.17 2009/10/22 20:54:30 blackdog Exp $

function video_filter_codec_info() {
  $codecs = array();

  $codecs['youtube'] = array(
    'name' => t('YouTube'),
    'callback' => 'video_filter_youtube',
    'regexp' => '/youtube\.com\/watch\?v=([a-z0-9\-_]+)/i',
    'ratio' => 425 / 355,
  );
  $codecs['google'] = array(
    'name' => t('Google Video'),
    'callback' => 'video_filter_google',
    'regexp' => '/video\.google\.[a-z]+\/videoplay\?docid=(\-?[0-9]+)/',
    'ratio' => 400 / 326,
  );
  $codecs['tangle'] = array(
    'name' => t('Tangle'),
    'callback' => 'video_filter_tangle',
    'regexp' => array(
                  '/tangle\.com\/view_video\.php\?viewkey=([a-z0-9]+)/',
                  '/tangle\.com\/view_video\?viewkey=([a-z0-9]+)/',
                ),
    'ratio' => 330 / 270,
  );
  $codecs['dailymotion'] = array(
    'name' => t('DailyMotion'),
    'callback' => 'video_filter_dailymotion',
    'regexp' => '/dailymotion\.com\/.*video\/([a-z0-9]+)/i',
    'ratio' => 420 / 336,
  );
  $codecs['eyespot'] = array(
    'name' => t('Eyespot'),
    'callback' => 'video_filter_eyespot',
    'regexp' => '/eyespot\.com\/.*r=([a-z0-9]+)/i',
    'ratio' => 432 / 407,
  );
  $codecs['revver'] = array(
    'name' => t('Revver'),
    'callback' => 'video_filter_revver',
    'regexp' => '/revver\.com\/video\/([0-9]+)/',
    'ratio' => 408 / 324,
  );
  $codecs['vimeo'] = array(
    'name' => t('Vimeo'),
    'callback' => 'video_filter_vimeo',
    'regexp' => '/vimeo\.com\/([0-9]+)/',
    'ratio' => 400 / 225,
  );
  $codecs['flickr_slideshows'] = array(
    'name' => t('Flickr Slideshows'),
    'callback' => 'video_filter_flickr_slideshows',
    'regexp' => '/flickr\.com\/photos\/([a-zA-Z0-9@_\-]+)\/sets\/([0-9]+)\/?[show]?\/?/i',
    'ratio' => 400 / 300,
  );
  $codecs['flickr_video'] = array(
    'name' => t('Flickr Video'),
    'callback' => 'video_filter_flickr_video',
    'regexp' => '/flickr\.com\/photos\/([a-zA-Z0-9@_\-]+)\/([0-9]+)/',
    'ratio' => 400 / 226,
  );
  $codecs['gamevideos'] = array(
    'name' => t('Game Videos'),
    'callback' => 'video_filter_gamevideos',
    'regexp' => '/gamevideos\.1up\.com\/video\/id\/([0-9]+)/',
    'ratio' => 500 / 319,
  );
  $codecs['metacafe'] = array(
    'name' => t('Meta Cafe'),
    'callback' => 'video_filter_metacafe',
    'regexp' => '/metacafe\.com\/watch\/([a-z0-9\-_]+)\/([a-z0-9\-_]+)/i',
    'ratio' => 400 / 345,
  );
  $codecs['gametrailers'] = array(
    'name' => t('Game Trailers'),
    'callback' => 'video_filter_gametrailers',
    'regexp' => array(
      '/gametrailers\.com\/player\/([0-9]+)/',
      '/gametrailers\.com\/video\/([a-z0-9\-_]+)\/([0-9]+)/',
    ),
    'ratio' => 480 / 392,
  );
  $codecs['collegehumor'] = array(
    'name' => t('College Humor'),
    'callback' => 'video_filter_collegehumor',
    'regexp' => '/collegehumor\.com\/video\:([0-9]+)/',
    'ratio' => 480 / 360,
  );
  $codecs['myspace'] = array(
    'name' => t('MySpace'),
    'callback' => 'video_filter_myspace',
    'regexp' => '/vids\.myspace\.com\/.*VideoID=([0-9]+)/i',
    'ratio' => 425 / 360,
  );
  $codecs['capped'] = array(
    'name' => t('Capped'),
    'callback' => 'video_filter_capped',
    'regexp' => '/capped\.tv\/([a-zA-Z0-9\-_]+)/',
    'ratio' => 425 / 355,
  );
  $codecs['bliptv'] = array(
    'name' => t('Blip.tv'),
    'callback' => 'video_filter_bliptv',
    'regexp' => array(
                  '@blip\.tv/rss/flash/([^"\&\?/]+)@i',
                  '@blip\.tv/file/view/([^"\&\?/]+)@i',
                  '@blip\.tv/file/([^"\&\?/]+)@i',
                  '@blip\.tv/play/([^"\&\?/]+)@i',
                ),
    'ratio' => 480 / 335,
  );
  $codecs['slideshare'] = array(
    'name' => t('Slideshare'),
    'callback' => 'video_filter_slideshare',
    'instructions' => t('You need to construct your own URL, using the "Wordpress Embed" code from Slideshare, extract the "id" and "doc" parts, and form the URL like this: slideshare.net/?id=1759622&amp;doc=usingdrupal-090723103440-phpapp01.'),
    'regexp' => '/slideshare\.net\/\?id=([a-z0-9]+).*doc=([a-z0-9-]+)/',
    'ratio' => 500 / 410,
  );
  $codecs['picasa_slideshows'] = array(
    'name' => t('Picasa Slideshows'),
    'callback' => 'video_filter_picasa_slideshows',
    'instructions' => t('You must use the URL of the RSS feed for the Picasa album:') .
                      '<ol>' .
                      '<li>' . t('View the album in Picasa (you should see thumbnails, not a slideshow).') . '</li>' .
                      '<li>' . t('Find the "RSS" link and click it.') . '</li>' .
                      '<li>' . t('Copy the resulting URL from the browser address bar.  Example: ') . '<br />' .
                      '<code>[video: http://picasaweb.google.com/data/feed/base/user/USER_NAME/albumid/5568104935784209834?alt=rss&kind=photo&hl=en_US]</code>' .
                      '</li>' .
                      '</ol>',
    'regexp' => '/picasaweb\.google\.com\/data\/feed\/base\/user\/([a-zA-Z0-9@_\-]+)\/albumid\/([a-z0-9]+)/i',
    'ratio' => 800 / 600,
  );

  return $codecs;
}

function video_filter_youtube($video) {
  $video['source'] = 'http://www.youtube.com/v/'.$video['codec']['matches'][1].($video['autoplay'] ? '&amp;autoplay=1' : '').'&amp;fs=1'.($video['related'] ? '' : '&amp;rel=0');

  return video_filter_flash($video);
}

function video_filter_google($video) {
  $video['source'] = 'http://video.google.com/googleplayer.swf?docId='.$video['codec']['matches'][1];

  return video_filter_flash($video);
}

function video_filter_tangle($video) {
  $video['source'] = 'http://www.tangle.com/flash/swf/flvplayer.swf?viewkey='.$video['codec']['matches'][1];

  return video_filter_flash($video);
}

function video_filter_dailymotion($video) {
  $video['source'] = 'http://www.dailymotion.com/swf/'.$video['codec']['matches'][1];

  return video_filter_flash($video);
}

function video_filter_eyespot($video) {
  $video['source'] = 'http://eyespot.com/flash/medialoader.swf?vurl=http%3A%2F%2Fdownloads.eyespot.com%2Fplay%3Fr%3D'.$video['codec']['matches'][1].'&_autoPlay='.($video['autoplay'] ? 'true' : 'false');

  return video_filter_flash($video);
}

function video_filter_revver($video) {
  $output = '<script src="http://flash.revver.com/player/1.0/player.js?mediaId:'.$video['codec']['matches'][1].';width:'.$video['width'].';height:'.$video['height'].';" type="text/javascript"></script>';

  return $output;
}

function video_filter_vimeo($video) {
  $video['source'] = 'http://www.vimeo.com/moogaloop.swf?clip_id='.$video['codec']['matches'][1].'&amp;server=www.vimeo.com&amp;fullscreen=1&amp;show_title=1&amp;show_byline=1&amp;show_portrait=0&amp;color=&amp;autoplay='.$video['autoplay'];

  return video_filter_flash($video);
}

function video_filter_flickr_slideshows($video) {
  $slideshow_player_url = 'http://www.flickr.com/apps/slideshow/show.swf?v=67348';
  $video['source'] = $slideshow_player_url . ($video['autoplay'] ? '&amp;autoplay=1' : '');

  $user_name = $video['codec']['matches'][1];
  $set_id = $video['codec']['matches'][2];

  $params['flashvars'] = "&amp;offsite=true&amp;lang=en-us&amp;page_show_url=%2Fphotos%2F$user_name%2Fsets%2F$set_id%2Fshow%2F&amp;page_show_back_url=%2Fphotos%2F$user_name%2Fsets%2F$set_id%2F&amp;set_id=$set_id&amp;jump_to=";

  return video_filter_flash($video, $params);
}

function video_filter_flickr_video($video) {
  $video['source'] = 'http://www.flickr.com/apps/video/stewart.swf?v=1.161';

  $params['flashvars'] = '&amp;photo_id='.$video['codec']['matches'][2].'&amp;flickr_show_info_box=true';

  return video_filter_flash($video, $params);
}

function video_filter_gamevideos($video) {
  $video['source'] = 'http://gamevideos.1up.com/swf/gamevideos12.swf?embedded=1&amp;fullscreen=1&amp;autoplay=0&amp;src=http://gamevideos.1up.com/do/videoListXML%3Fid%3D'.$video['codec']['matches'][1];

  return video_filter_flash($video);
}

function video_filter_metacafe($video) {
  $video['source'] = 'http://metacafe.com/fplayer/'.$video['codec']['matches'][1].'/'.$video['codec']['matches'][2].'.swf';

  return video_filter_flash($video);
}

function video_filter_gametrailers($video) {
  if (is_numeric($video['codec']['matches'][1])) {
    $match = $video['codec']['matches'][1];
  }
  elseif (is_numeric($video['codec']['matches'][2])) {
    $match = $video['codec']['matches'][2];
  }
  $video['source'] = 'http://www.gametrailers.com/remote_wrap.php?mid='.$match;

  return video_filter_flash($video, $params);
}

function video_filter_collegehumor($video) {
  $video['source'] = 'http://www.collegehumor.com/moogaloop/moogaloop.swf?clip_id='.$video['codec']['matches'][1].'&amp;fullscreen=1';

  return video_filter_flash($video);
}

function video_filter_myspace($video) {
  $video['source'] = 'http://mediaservices.myspace.com/services/media/embed.aspx/m='.$video['codec']['matches'][1];

  return video_filter_flash($video, $params);
}

function video_filter_capped($video) {
  $video['source'] = 'http://capped.micksam7.com/playeralt.swf?vid='.$video['codec']['matches'][1];

  return video_filter_flash($video);
}

function video_filter_bliptv($video) {
  $id = $video['codec']['matches'][1];
  
  // Since video ID in URL is different than in embed code, use API
  // to lookup the embed code video ID. Adapted from emfield.module.
  $result = drupal_http_request('http://blip.tv/file/' . $id . '?skin=api');

  if ($result->code == 200) {
    $parser = drupal_xml_parser_create($result->data);
    $vals = array();
    $index = array();
    xml_parse_into_struct($parser, $result->data, $vals, $index);
    xml_parser_free($parser);
  
    $response = array();
    $response['_emfield_arghash'] = $arghash;
    $level = array();
    $start_level = 1;
    foreach ($vals as $xml_elem) {
      if ($xml_elem['type'] == 'open') {
        if (array_key_exists('attributes', $xml_elem)) {
          list($level[$xml_elem['level']], $extra) = array_values($xml_elem['attributes']);
        }
        else {
          $level[$xml_elem['level']] = $xml_elem['tag'];
        }
      }
      if ($xml_elem['type'] == 'complete') {
        $php_stmt = '$response';
        while ($start_level < $xml_elem['level']) {
          $php_stmt .= '[$level['. $start_level .']]';
          $start_level++;
        }
        $php_stmt .= '[$xml_elem[\'tag\']][] = $xml_elem[\'value\'];'. $php_stmt .'[$xml_elem[\'tag\']][] = $xml_elem[\'attributes\'];';
        eval($php_stmt);
        $start_level--;
      }
    }
    $id = $response['EMBEDLOOKUP'][0];
  }
  
  $video['source'] = 'http://blip.tv/play/' . $id;
  $params = array(
    'allowscriptaccess' => 'always',
  );
  
  return video_filter_flash($video, $params);
}

function video_filter_slideshare($video) {
  $video['source'] = 'http://static.slideshare.net/swf/ssplayer2.swf?id=' . $video['codec']['matches'][1] . '&amp;doc=' . ($video['codec']['matches'][2]);

  return video_filter_flash($video);
}

function video_filter_picasa_slideshows($video) {
  $video['source'] = 'http://picasaweb.google.com/s/c/bin/slideshow.swf';

  $user_name = $video['codec']['matches'][1];
  $set_id = $video['codec']['matches'][2];

  $params['flashvars'] = "host=picasaweb.google.com&amp;&amp;feat=flashalbum&amp;RGB=0x000000&amp;feed=http%3A%2F%2Fpicasaweb.google.com%2Fdata%2Ffeed%2Fapi%2Fuser%2F" . $user_name . "%2Falbumid%2F" . $set_id . "%3Falt%3Drss%26kind%3Dphoto%26" . ($video['autoplay'] ? '' : '&amp;noautoplay=1');

  return video_filter_flash($video, $params);
}