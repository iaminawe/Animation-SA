<?php
// $Id: veoh.inc,v 1.1.2.1 2009/05/20 22:47:51 aaron Exp $

define('VIDEO_CCK_VEOH_MAIN_URL', 'http://www.veoh.com/');
define('VIDEO_CCK_VEOH_API_INFO', 'http://www.veoh.com/restApiDoc/restReference.html');
define('VIDEO_CCK_VEOH_API_APPLICATION_URL', 'http://www.veoh.com/developers.html');
define('VIDEO_CCK_VEOH_XML', 'http://www.veoh.com/rest/video/');

function video_cck_veoh_info() {
  $name = t('Veoh');
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Show related videos'), t('No'), t('This is embedded in the video itself when enabled; currently not available with other providers. Set the feature above.')),
    array(t('Thumbnails'), t('Yes'), t('May not currently resize thumbnails. Must have an API key for thumbnails at the moment, although research is underway to determine an alternative to this. Set your API key above.')),
  );
  return array(
    'provider' => 'veoh',
    'name' => $name,
    'url' => VIDEO_CCK_VEOH_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !veoh. You can learn more about its !api here.', array('!veoh' => l($name, VIDEO_CCK_VEOH_MAIN_URL, array('target' => '_blank')), '!api' => l(t('API'), VIDEO_CCK_VEOH_API_INFO, array('target' => '_blank')))),
    'supported_features' => $features,
  );
}

function video_cck_veoh_settings() {
  $form['veoh']['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('Veoh API'),
    '#description' => t('If you wish to be able to display Veoh thumbnails automatically, you will first need to apply for an API Developer Key from the !veoh. Note that you do not need this key to display Veoh videos themselves.', array('!veoh' => l('Veoh Developer Profile page', VIDEO_CCK_VEOH_API_APPLICATION_URL, array('target' => '_blank')))),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['veoh']['api']['video_cck_veoh_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Veoh API Key'),
    '#default_value' => variable_get('video_cck_veoh_api_key', ''),
    '#description' => t('Please enter your Veoh Developer Key here.'),
  );
  $form['veoh']['api']['video_cck_veoh_api_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Veoh API Secret'),
    '#default_value' => variable_get('video_cck_veoh_api_secret', ''),
    '#description' => t('If you have a secret for the Veoh API, enter it here.'),
  );
  return $form;
}


function video_cck_veoh_request($embed, $cacheable = TRUE) {
  $args = array('docid' => $embed);
  return module_invoke('emfield', 'request_xml', 'veoh', VIDEO_CCK_VEOH_XML . $embed .'/details', $args, $cacheable);
}

function video_cck_veoh_extract($embed = '') {
  return array(
    '@http://www\.veoh\.com/videos/([^"\?]+)@i',
    '@http://www\.veoh\.com/videodetails2\.swf\?permalinkId=([^"\&]*)@i',
  );
}

function video_cck_veoh_embedded_link($video_code) {
  return 'http://www.veoh.com/videos/'. $video_code;
}

function theme_video_cck_veoh_flash($embed, $width, $height, $autoplay) {
  if ($embed) {
    $autoplay = $autoplay ? '&videoAutoPlay=1' : '&videoAutoPlay=0';

    $output .= '<embed src="http://www.veoh.com/videodetails2.swf?permalinkId='. $embed .'&id=9183600&player=videodetailsembedded'. $autoplay .'" allowFullScreen="true" width="'. $width .'" height="'. $height .'" bgcolor="#FFFFFF" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer"></embed>';
  }
  return $output;
}

function video_cck_veoh_check_thumbnail($thumbnail_check) {
  if ($thumbnail_status=@fopen($thumbnail_check, "r")) {
    fclose($thumbnail_status);
    return $thumbnail_status;
  }
  return NULL;
}

function video_cck_veoh_thumbnail($field, $item, $formatter, $node, $width, $height) {
  $thumbid = $item['value'];
  //$xml = video_cck_veoh_request($item['value']);
  //print_r($xml);
  // make the thumb index zero to follow their standard web tag format.

  // - Rysk
  $thumbnail = 'http://p-images.veoh.com/thumb.out?imageId=thumb-'. $thumbid .'-'. rand(0, 30) .'.jpg';
  if (video_cck_veoh_check_thumbnail($thumbnail) != NULL) {
    return $thumbnail;
  } 
  else {
    $url = 'http://www.veoh.com/rest/video/'. $thumbid .'/details';
    $content = file_get_contents($url);
    if ($content) {
      print '(start)<br>';
      print $content;
      print '(end)<br>';
      $start = strpos($content, 'fullMedResImagePath="')+21;
      $end = strpos($content, '"', $start);
      $thumbnail = substr($content, $start, $end-$start);
    }
    return $thumbnail;
  }
}

function video_cck_veoh_video($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_veoh_flash', $embed, $width, $height, $autoplay);
  return $output;
}

function video_cck_veoh_preview($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_veoh_flash', $embed, $width, $height, $autoplay);
  return $output;
}
