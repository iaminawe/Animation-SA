// $Id: uc_donate_pane.js,v 1.1 2008/05/02 00:36:05 greenskin Exp $

if (Drupal.jsEnabled) {
  var donateTotal = 0;
  $(document).ready(function() {
    $("input.donate-amount").each(function(i) {
      donateTotal+= parseFloat($(this).val());
      
      $(this).click(function() {
        highlight(this);
      });
      
      $(this).change(function() {
        donateTotal = setTotal();
        $("#donate_total span").empty().append(donateTotal);
        var thisTotal = formatTotal($(this).val());
        $(this).val(thisTotal);
        $('h4#donate_total').highlightFade({color:'yellow',speed:2000,iterator:'sinusoidal'});
        
        if (donateTotal > 0) {
          set_line_item('donations','Added Donations',donateTotal,-1);
        }
      });
    });
    
    donateTotal = formatTotal(donateTotal);
    $("#donate-pane").append("<div class='clear-block'><h4 id='donate_total'>Donation Total: $<span>"+donateTotal+"</span></h4></div>");
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