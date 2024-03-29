<?php
// $Id: dailymotion.inc,v 1.4.2.1 2009/05/20 22:47:51 aaron Exp $

define('VIDEO_CCK_DAILYMOTION_MAIN_URL', 'http://www.dailymotion.com/');

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
function video_cck_dailymotion_info() {
  $name = t('Dailymotion');
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Thumbnails'), t('No'), t('')),
  );
  return array(
    'provider' => 'dailymotion',
    'name' => $name,
    'url' => VIDEO_CCK_DAILYMOTION_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !dailymotion. You can learn more about its !api here.', array('!dailymotion' => l($name, VIDEO_CCK_DAILYMOTION_MAIN_URL, array('target' => '_blank')), '!api' => l(t('API'), VIDEO_CCK_DAILYMOTION_API_INFO, array('target' => '_blank')))),
    'supported_features' => $features,
  );
}

/**
 * hook video_cck_PROVIDER_settings
 * this should return a subform to be added to the video_cck_settings() admin settings page.
 * note that a form field will already be provided, at $form['PROVIDER'] (such as $form['dailymotion'])
 * so if you want specific provider settings within that field, you can add the elements to that form field.
 */
function video_cck_dailymotion_settings() {
  $form = array();
  return $form;
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
function video_cck_dailymotion_extract($embed = '') {
  // http://www.dailymotion.com/us/cluster/news/featured/video/x3xk8v_primary-smackdown-obama-girl-return_fun
  // http://www.dailymotion.com/barelypolitical/video/x3xk8v_primary-smackdown-obama-girl-return_fun
  // http://www.dailymotion.com/barelypolitical/video/x3xk8v
  // <div><object width="420" height="252"><param name="movie" value="http://www.dailymotion.com/swf/x3xk8v" /></param><param name="allowFullScreen" value="true"></param><param name="allowScriptAccess" value="always"></param><embed src="http://www.dailymotion.com/swf/x3xk8v" type="application/x-shockwave-flash" width="420" height="252" allowFullScreen="true" allowScriptAccess="always"></embed></object><br /><b><a href="http://www.dailymotion.com/video/x3xk8v_primary-smackdown-obama-girl-return_fun">Primary Smackdown: Obama Girl Returns</a></b><br /><i>Uploaded by <a href="http://www.dailymotion.com/BarelyPolitical">BarelyPolitical</a></i></div>
  // <div><object width="420" height="252"><param name="movie" value="http://www.dailymotion.com/swf/x3xk8v"></param><param name="allowFullScreen" value="true"></param><param name="allowScriptAccess" value="always"></param><embed src="http://www.dailymotion.com/swf/x3xk8v" type="application/x-shockwave-flash" width="420" height="252" allowFullScreen="true" allowScriptAccess="always"></embed></object><br /><b><a href="http://www.dailymotion.com/video/x3xk8v_primary-smackdown-obama-girl-return_fun">Primary Smackdown: Obama Girl Returns</a></b><br /><i>Uploaded by <a href="http://www.dailymotion.com/BarelyPolitical">BarelyPolitical</a></i></div>
//   if (preg_match('@dailymotion\.com@i', $embed, $matches)) {
//     if (preg_match('@/([^/_]+)_@i', $embed, $matches)) {
//       return $matches[0];
//     }
//   }
  if (preg_match('@dailymotion\.com/swf/([^"\&]+)@i', $embed, $matches)) {
    return $matches[1];
  }
  if (preg_match('@dailymotion\.com@i', $embed, $matches)) {
    if (preg_match('@/([^/_]+)_@i', $embed, $matches)) {
      return $matches[1];
    }
  }
  return array();
}

/**
 * hook video_cck_PROVIDER_embedded_link($video_code)
 * returns a link to view the video at the provider's site
 *  @param $video_code
 *    the string containing the video to watch
 *  @return
 *    a string containing the URL to view the video at the original provider's site
 */
function video_cck_dailymotion_embedded_link($video_code) {
  return 'http://www.dailymotion.com/swf/'. $video_code;
}

/**
 * the embedded flash displaying the dailymotion video
 */
function theme_video_cck_dailymotion_flash($embed, $width, $height, $autoplay) {
  if ($embed) {
    if ($autoplay) {
      $autoplay_value = '&autoStart=1';
    }
    $output .= "    <object type=\"application/x-shockwave-flash\" height=\"$height\" width=\"$width\" data=\"http://www.dailymotion.com/swf/$embed". $autoplay_value ."\" id=\"VideoPlayback\">
      <param name=\"movie\" value=\"http://www.dailymotion.com/swf/$embed". $autoplay_value ."\" />
      <param name=\"allowScriptAcess\" value=\"always\" />
      <param name=\"allowFullScreen\" value=\"true\" />
      <param name=\"quality\" value=\"best\" />
      <param name=\"bgcolor\" value=\"#FFFFFF\" />
      <param name=\"scale\" value=\"noScale\" />
      <param name=\"salign\" value=\"TL\" />
      <param name=\"FlashVars\" value=\"playerMode=embedded$autoplay_value\" />
      <param name=\"wmode\" value=\"transparent\" />
    </object>\n";
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
function video_cck_dailymotion_thumbnail($field, $item, $formatter, $node, $width, $height) {
  return 'http://www.dailymotion.com/thumbnail/160x120/video/'. $item['value'];
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
function video_cck_dailymotion_video($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_dailymotion_flash', $embed, $width, $height, $autoplay);
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
function video_cck_dailymotion_preview($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_dailymotion_flash', $embed, $width, $height, $autoplay);
  return $output;
}
