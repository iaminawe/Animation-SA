// $Id: poormanscron.js,v 1.1.4.3 2010/01/17 00:23:25 davereid Exp $

/**
 * Checks to see if the cron should be automatically run.
 */
Drupal.cronCheck = function(context) {
  if (Drupal.settings.cron.runNext || false) {
    $('body:not(.cron-check-processed)', context).addClass('cron-check-processed').each(function() {
      // Only execute the cron check if its the right time.
      if (Math.round(new Date().getTime() / 1000.0) >= Drupal.settings.cron.runNext) {
        $.get(Drupal.settings.cron.basePath + '/run-cron-check');
      }
    });
  }
};

if (Drupal.jsEnabled) {
  $(document).ready(Drupal.cronCheck);
}
