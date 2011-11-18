// $Id: panels_carousel.js,v 1.1 2007/08/14 23:23:40 wimleers Exp $

$(document).ready(function() {
	var i;
	var selector;
	var settings;

  // Add our custom easing function.
  jQuery.easing["QuartEaseOut"] = function(p, t, b, c, d) {
    return -c * ((t=t/d-1)*t*t*t - 1) + b;
  };

	// Waits until the height of the element that contains the carousel is
	// greater than zero, then renders the carousel.
	function renderCarouselOnHeight($e, settings) {
		if ($e.height()) {
			$e.jcarousel(settings);
		}
		else {
			setTimeout(function(){ renderCarouselOnHeight($e, settings); }, 50);
		}
	}

	for (i in Drupal.settings.jcarousel) {
		selector = Drupal.settings.jcarousel[i]['selector'];
		settings = Drupal.settings.jcarousel[i]['settings'];

		// Render the carousel when the height is greater than zero. This prevents
		// errors being spit out by the jCarousel plugin. An occurrence of this
		// weird problem is at the "edit content" page of Panel Pages.
		renderCarouselOnHeight($(selector), settings);
	}
});
