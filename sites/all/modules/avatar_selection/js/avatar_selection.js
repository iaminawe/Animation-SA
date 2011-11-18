/* $Id: avatar_selection.js,v 1.1.2.1.2.12 2009/06/07 22:50:33 snpower Exp $ */
function radio_button_handler() {
  // handle radio buttons
  $('div.user-avatar-select input.form-radio').hide();
  $('div.user-avatar-select img').hover(
    function(){
      $(this).addClass("avatar-hover");
    },
    function(){
      $(this).removeClass("avatar-hover");
    }
  );
}

function image_click_handler() {
  $('div.user-avatar-select img').bind("click", function(){
    $("div.user-avatar-select img.avatar-select").each(function(){
      $(this).removeClass("avatar-select");
      $(this).parent().children("input").attr("checked", "");
    });
    $(this).addClass("avatar-select");
    $(this).parent().children("input").attr("checked", "checked");
  });
}

if (Drupal.jsEnabled) {
  $(document).ready(function () {

    // handle radio buttons
    radio_button_handler();

    // handle image selection
    image_click_handler();
  });
}


