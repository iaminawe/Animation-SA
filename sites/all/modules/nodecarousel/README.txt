NodeCarousel
==============

The nodecarousel module provides you with blocks that allow you to display various nodes to your user in a smooth scrolling side-to-side (or top to bottom) display.
Although the obvious thing to display is a set of pictures, the nodecarousel module could be used to scroll text headlines or links for your users to view as well.
The carousel can present a short set list of items, it can automatically fetch more items (via AJAX) when the user reaches the end, and it can even automatically
scroll for the user - all of these options are set via the options page at admin/build/nodecarousel.

The NodeCarousel module currently depends upon nodequeue and jquery_update.

The basics of setting up a simple nodecarousel aren't too complex - there's basically four steps.
1) Decide upon and set up your source.
2) Create an override for theme("nodecarousel_node") and possibly theme("nodecarousel")
3) Create the nodecarousel on your website and select how it works.
4) Do some cleanup css.

1: The Source
-------------
There's three possible ways to choose what nodes you display in your nodecarousel: you can pick a nodequeue to read from (very easy), you can choose node types and/or
taxonomy terms to fetch nodes from, or you can implement hook_nodecarousel() in your module, which will return node objects to the carousel each time it needs more.

If you choose a nodequeue then you'll want to set up a nodequeue for your use, and then when you get to step three you can choose that nodequeue from the list of them, and
then later in the list under Sort Order: you'll choose 'Nodequeue order' and either 'Ascending' or 'Descending'.

If you want to pick from node types or taxonomy terms (or both), then note down what you'll be fetching.  You'll need to set under Sort Order: the order of the nodes,
with your options being 'Date Created', 'Date Updated', 'Title', 'Node ID', 'Random', or 'Author Name', along with options for Ascending or Descending order.  If these
don't satisfy your needs, you may want to continue on to the next option.

Finally, hook_nodecarousel($name, $start_position, $number_fetch, $nid) provides you with the option to present whatever nodes you wish in whatever order you like.

Name - The name of the nodecarousel, established on the nodecarousel admin page.  This is useful for making sure that you're providing the right nodes to the right
carousel - it's quite possible to have several of these on the same page.
Start_Position - The index to fetch from.  Although on a static nodecarousel this will be usually 0, if you're using a dynamic nodecarousel which retrieves more items
via AJAX, this will indicate which nodes are desired.
Number_Fetch - The number of nodes to return.  You can return fewer.  If you return none, and it's a dynamic nodecarousel, it will assume you're done and not ask for more.
Nid - Node id.  If the nodecarousel is on a node page, then you can use this value to retrieve related information - such as other images in the same gallery if the user
is viewing a given image, for example.  If the block isn't on a node page, this should be -1.

Just return any and all nodes you find as an array of node objects.

2: The Presentation
-------------------
Both the node and the nodecarousel itself are set up in theme functions, 'theme_nodecarousel_node' and 'theme_nodecarousel'.  If you do override theme_nodecarousel, I
suggest either copying the existing function and making minor edits to it, as the code does require an <ul> with a particular class (jcarousel-target) and name.

However, theme_nodecarousel_node is highly themeable - the default only displays the title of each node as a link.  Feel free to set it up as you like,
with a few suggestions:
a) I strongly suggest wrapping the entire node presentation in a div with the class "node-carousel-item".
b) I suggest wrapping the title of the node in a div or span with the class 'node-carousel-title'.
c) If you want to have an index list under the nodecarousel, displaying links that can be clicked to move to show that node, present the text you want to show as the
index inside of a div or span with the class 'node-carousel-label'.  It's fine to use CSS to hide this label - this is just the way you tell nodecarousel that this text
is what you want it to provide as a label.  If you're not going to use that option, feel free to omit this label.

Beyond that, style it up as you like and return the result as a string.

3: Create the nodecarousel
--------------------------
Having already installed the nodecarousel module, head to admin/build/nodecarousel and click on 'Add' to create your nodecarousel.  You'll first need to come up with
a unique nodecarousel name, with letters and underscores only.  That done, there's a series of options to choose:

Access:
Select the user roles who can see this nodecarousel.  If you select none of them, then everyone will be able to use it.

Description:
A description, for your use so you can remember what it's for.

Title:
The title to display with the nc block.

Node Source:
As you decided in part one, choose node type/taxonomy, queue, or hook.  If you choose node type, you'll need to pick
out the types or terms to present.  If you choose node queue, then you'll need to pick which node queue to read from.

Data Collection:
If Static, then all nodes that will be displayed will be fetched on the page load. If using a Dynamic data collection,
then additional nodes will be fetched via AJAX when the last node is displayed.

Number to Fetch:
If static, this is the total number of items to have in the carousel. If Dynamic, then initially, and each time the user reaches the end,
this number of nodes will be added to the carousel.

Carousel Orientation:
Which direction the nodecarousel will scroll - Vertical or Horizontal.

Wrap Style of Carousel:
The wrap style indicates what happens when the user gets to one end, or the other, of the carousel. If 'None', nothing happens. If 'From Last, return to First',
then when the user gets to the end and tries to go further, they are sped back to the beginning. If 'From First, proceed to Last',
then if they are the first item and use the Previous button, they will advance to the end. 'Both' activates both of those. 'Circular' means that after
viewing the last and proceeding to the next, the first one is shown as the next item.

Autoscroll:
The nodecarousel will automatically scroll every so many seconds, if a value greater than 0 is put in.  If you don't want it to scroll for you, just put in zero.

Index Display:
An index display is an unordered list of links that the user can click on to scroll instantly to that item.  If you don't want that, set it to 'No Index'.  If you
set it to 'Numeric Index' then the links will be numbered from 1 to n, if 'Title Index' is chosen, then the links will be the titles of each node (themed with
'node-carousel-title', like we discussed in step 2), and if 'Index written in theme' is picked, then it's whatever was labeled with 'node-carousel-index'.  (Don't forget
to set the index field to hidden in your css.)
     This doesn't really work with dynamic carousels, because the unordered list is only populated on the initial load.  If you want to mess with dynamic displays
with an index, I suggest working up something with the 'Javascript Scroll Event Handler', below.

Number visible:
The number of nodes you want it to display at any time.  If you set it to 0, then the code will just display as many as fit, depending on how wide (or tall) you've
got the li items displaying.

Start Position:
Which node, starting from #1, to display.  If you wanted it to start by display the middle item, then you might set this to a middle value.

Number to Scroll by:
Just what it says - 1 is often a good value, or the number visible also isn't a bad idea.

Animation Speed:
How quickly the items slide out of and into view.  You can use the standard "slow" or "fast" that jQuery uses, or you can give it a number of milliseconds
which represents how long the slide takes.  If you set it to 0, no animation happens, and the next items just appear in place.

Previous button text:
Not really a button, but the contents of the div that the user will click to scroll backwards.  If you intend to theme the div with a background image for users to click,
you can set this to nothing, otherwise I suggest '<' or something similar.

Next button text:
Just as with the previous, the contents of the div that the user will click to scroll forwards.

First button text:
This button lets the user scroll all the way to node 1 with one click - if you don't want to present this, or if you intend to decorate with an image, leave blank.

Last button text:
Similarly, the button that scrolls you to the last node.  Note that if you've got a dynamic carousel, the user will go to see the last node that's on the page yet,
and then new nodes will be loaded via AJAX which the user will not be scrolled to yet.

Sort Order:
The order to show the nodes in.  If you've chosen the source to be Node/Taxonomy, then you need to choose how to order the nodes.  If you've chosen Node Queue, then
you need to choose Node Queue order.  If you're using hook_nodecarousel(), then don't choose anything.

Sort Order (ascending/descending):
Simple enough - ignored for hook_nodecarousel, though.

Javascript Scroll Event Handler:
In the case that you need something special to happen after the user scrolls, then you can write a javascript function and put the name of the function here.
The parameters are carousel, index, direction - the carousel is the carousel object, index is the position the user is at now, and direction is one of 'prev',
'next', or 'init'.  (Init is only called when the page loads, and you can do additional setup using it.)

4: Cleanup and CSS
------------------
One of the little tricky bits about using nodecarousel is that you sometimes have to sit down with pencil and paper, decide how large you want the display to be,
and figure out the width/height of each li item (or what's inside of the li item) should be from that.  For an example, let's say you want to have your nodecarousel
be horizontal, hold three items, and it needs to fit inside of about 350px space.  With that, you want to specify that your list items are each about... 116 px wide.
Don't forget margins!  You might, for prettier presentation, decide to go with about a 110 px li, throw a margin of 3px on either side of it, and there you go -
the jcarousel code will set the width of the clip div to 348px wide, and it'll display nicely.  Further theming can provide quite striking results.


NodeCarousel Structure:
=======================
The Nodecarousel consists of an unordered list with items that displays behind a 'clip' div with 'overflow:hidden' set on it.  As the user scrolls, the ul is shifted
to one side or the other, thus changing which items are displaying in the div.  This clip div, and a number of the classes and other items that display on the screen
are generated by the jcarousel code, so when you're theming how large you want each li to be, you want to use the ids and classes that are in the code before the
javascript hits, because when the code is deciding to make the clip 250px wide because each element is 50px and you want five showing, you don't want to be using
the later-applied classes to widen the elements to 100px wide - because they'll look bad.

     I suggest targetting the "ul#nc_<name>" for the unordered list, and the "div.node-carousel-item" - or if you change the theme to use some other class, whatever
you picked there.

Once the jcarousel has been loaded, the structure looks something like this - items in ## vary depending on the carousel.:
<div class="jcarousel-container jcarousel-container-horizontal nc_#name#" style="display: block;">
  <div id="nc_first_#nodecarousel id#" class="jcarousel-first">#first text#</div>
  <div class="jcarousel-prev jcarousel-prev-horizontal" style="display: block;">Prev</div>
  <div class="jcarousel-next jcarousel-next-horizontal" style="display: block;">Next</div>
  <div id="nc_last_#nodecarousel id#" class="jcarousel-last">Last</div>
  <div class="jcarousel-clip jcarousel-clip-horizontal nc_clip_test_access">
    <ul id="nc_#name#" class="jcarousel_target jcarousel-list jcarousel-list-horizontal" style="width: #computed width#; left: 0pt;">
      <li>
        <!-- Stuff -->
      </li>
      <!-- Various list items.... -->
    </ul>
  </div>
</div>