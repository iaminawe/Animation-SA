<?php
// $Id: livevideo.inc,v 1.3.6.1 2009/05/20 22:47:51 aaron Exp $

define('VIDEO_CCK_LIVEVIDEO_MAIN_URL', 'http://www.livevideo.com/');
define('VIDEO_CCK_LIVEVIDEO_API_INFO', 'http://www.livevideo.com/api/default.aspx');
define('VIDEO_CCK_LIVEVIDEO_API_APPLICATION_URL', 'http://www.livevideo.com/profile/admin/editdeveloperprofile.aspx');
define('VIDEO_CCK_LIVEVIDEO_REST_ENDPOINT', 'http://www.livevideo.com/api/');

/**
 * hook video_cck_PROVIDER_info
 * this returns information relevant to a specific 3rd party video provider
 * @return
 *   an array of strings requested by various admin and other forms
 *   'name' => the translated name of the provider
 *   'url' => the url to the main page for the provider
 *   'settings_description' => a description of the provider that will be posted in the admin settings form
 *   'supported_features' => an array of rows describing the state of certain supported features by the provider.
 *      These will be rendered in a table, with the columns being 'Feature', 'Supported', 'Notes'.
 */
function video_cck_livevideo_info() {
  $name = t('Live Video');
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Thumbnails'), t('Yes'), ''),
  );
  return array(
    'provider' => 'livevideo',
    'name' => $name,
    'url' => VIDEO_CCK_LIVEVIDEO_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !livevideo. You can learn more about its !api here.', array('!livevideo' => l($name, VIDEO_CCK_LIVEVIDEO_MAIN_URL, array('target' => '_blank')), '!api' => l(t('API'), VIDEO_CCK_LIVEVIDEO_API_INFO, array('target' => '_blank')))),
    'supported_features' => $features,
  );
}

/**
 * hook video_cck_PROVIDER_settings
 * this should return a subform to be added to the video_cck_settings() admin settings page.
 * note that a form field will already be provided, at $form['PROVIDER'] (such as $form['livevideo'])
 * so if you want specific provider settings within that field, you can add the elements to that form field.
 */
function video_cck_livevideo_settings() {
  $form['livevideo']['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('Live Video API'),
    '#description' => t('If you wish to be able to display Live Video thumbnails automatically, you will first need to apply for an API Developer Key from the !livevideo. Note that you do not need this key to display Live Video videos themselves.', array('!livevideo' => l('Live Video Developer Profile page', VIDEO_CCK_LIVEVIDEO_API_APPLICATION_URL, array('target' => '_blank')))),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['livevideo']['api']['video_cck_livevideo_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Live Video API Key'),
    '#default_value' => variable_get('video_cck_livevideo_api_key', ''),
    '#description' => t('Please enter your Live Video Developer Key here.'),
  );
  return $form;
}

/**
 * this is a wrapper for video_cck_request_xml that includes livevideo's api key
 */
function video_cck_livevideo_request($method, $args = array(), $cached = true) {
  $args['developerId'] = trim(variable_get('video_cck_livevideo_api_key', ''));

  $request = module_invoke('emfield', 'request_xml', 'livevideo', VIDEO_CCK_LIVEVIDEO_REST_ENDPOINT . $method, $args, $cached);
  return $request;
}

/**
 * hook video_cck_PROVIDER_extract
 * this is called to extract the video code from a pasted URL or embed code.
 * @param $embed
 *   an optional string with the pasted URL or embed code
 * @return
 *   either an array of regex expressions to be tested, or a string with the video code to be used
 *   if the hook tests the code itself, it should return either the string of the video code (if matched), or an empty array.
 *   otherwise, the calling function will handle testing the embed code against each regex string in the returned array.
 */
function video_cck_livevideo_extract($embed = '') {
  // <div><embed src="http://www.livevideo.com/flvplayer/embed/591C1350DD174FE0B10C4DCFC88981DA" type="application/x-shockwave-flash" quality="high" WIDTH="445" HEIGHT="369" wmode="transparent"></embed><br/><a href="http://www.livevideo.com/video/embedLink/591C1350DD174FE0B10C4DCFC88981DA/236172/mascot-bloopers-video.aspx">Mascot Bloopers Video</a></div>
  // http://www.livevideo.com/video/591C1350DD174FE0B10C4DCFC88981DA/mascot-bloopers-video.aspx
  // NOTE: the order of the following matters very much in this case...
  return array(
    '@livevideo\.com/flvplayer/embed/([^\"]*)\"@i',
    '@livevideo\.com/video/([^/]*)/@i',
  );
}

/**
 * hook video_cck_PROVIDER_embedded_link($video_code)
 * returns a link to view the video at the provider's site
 *  @param $video_code
 *    the string containing the video to watch
 *  @return
 *    a string containing the URL to view the video at the original provider's site
 */
function video_cck_livevideo_embedded_link($video_code) {
  $method = 'GetVideoDetails.ashx';
  $args = array('videoId' => $video_code);
  $request = video_cck_livevideo_request($method, $args);
  $url = $request['VIDEODETAILS']['VIEWURL'][0];
  return $url;
}

/**
 * the embedded flash displaying the livevideo video
 */
function theme_video_cck_livevideo_flash($embed, $width, $height, $autoplay) {
  if ($embed) {
    $autostart = $autoplay ? '&autoStart=1' : '';
    $output .= '<embed src="http://www.livevideo.com/flvplayer/embed/'. $embed . $autostart .'" type="application/x-shockwave-flash" quality="high" WIDTH="'. $width .'" HEIGHT="'. $height .'" wmode="transparent"></embed>';
  }
  return $output;
}

/**
 * hook video_cck_PROVIDER_thumbnail
 * returns the external url for a thumbnail of a specific video
 * TODO: make the args: ($embed, $field, $item), with $field/$item provided if we need it, but otherwise simplifying things
 *  @param $field
 *    the field of the requesting node
 *  @param $item
 *    the actual content of the field from the requesting node
 *  @return
 *    a URL pointing to the thumbnail
 */
function video_cck_livevideo_thumbnail($field, $item, $formatter, $node, $width, $height) {
  $method = 'GetVideoDetails.ashx';
  $args = array('videoId' => $item['value']);
  $request = video_cck_livevideo_request($method, $args);
  $tn = $request['VIDEODETAILS']['DEFAULTTHUMBNAIL'][0];
  return $tn;
}

/**
 * hook video_cck_PROVIDER_video
 * this actually displays the full/normal-sized video we want, usually on the default page view
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function video_cck_livevideo_video($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_livevideo_flash', $embed, $width, $height, $autoplay);
  return $output;
}

/**
 * hook video_cck_PROVIDER_video
 * this actually displays the preview-sized video we want, commonly for the teaser
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function video_cck_livevideo_preview($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_livevideo_flash', $embed, $width, $height, $autoplay);
  return $output;
}
