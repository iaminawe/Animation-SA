// $Id: uc_donate.js,v 1.1 2008/05/02 00:36:05 greenskin Exp $

if (Drupal.jsEnabled) {
  var donateTotal = 0;
  $(document).ready(function() {
    var donateTotal = 0;
    $(".gift_form .form-item input").each(function(i) {
      donateTotal = parseFloat($(this).val()) + donateTotal;
      $(this).change(function() {
        donateTotal = setTotal();
        $("#donate_total span").empty().append(donateTotal);
        var thisTotal = formatTotal($(this).val());
        $(this).val(thisTotal);
        $('h4#donate_total').highlightFade({color:'yellow',speed:2000,iterator:'sinusoidal'});
        // $('h4#donate_total').click(function() {
        // });
      });
      
      $(this).click(function() {
        highlight(this);
      });
    });
    donateTotal = formatTotal(donateTotal);
    $("div.gift_submit").prepend("<h4 id='donate_total'>Total: $<span>"+donateTotal+"</span></h4>");
    $("div.gift_submit").prepend("<div id='donate_update'>Update Total</div>");
  });
  
  function setTotal() {
    var newTotal = 0;
    $(".gift_form .form-item input").each(function(i) {
      newTotal = newTotal + parseFloat($(this).val());
    });
    newTotal = formatTotal(newTotal);
    return newTotal;
  }
  
  function formatTotal(total) {
    var newTotal = Math.round(total*100)/100;
    newTotal = newTotal.toFixed(2);
    return newTotal;
  }
  
  function highlight(field) {
    field.focus();
    field.select();
  }
}