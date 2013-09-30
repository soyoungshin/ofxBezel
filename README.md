ofxBezel
========

An openframeworks addon to perform bezel compensation when displaying over multiple monitors in a grid-like fashion. (see example images folder)

Most of the work occurs within a GL shader, so it may not work on all hardware, but the most recent version works on a standard macbook (which I don't belive has a fancy graphics card).

This is super helpful if you have an app that is displayed over multiple monitors, and you don't want to draw a portion of the total displayed image on each monitor separately.


How to run the example
======================

1. Download this git bundle, and drop it in to your addons folder. 
2. There is an example xcode and visual studio project in this directory. Drop the example in to your apps/myApps folder.
3. Run the app with the given height/width dimensions from main.cpp. Press 'enter' to show the debug screen. Press 'enter' again to show the feed with video.


What's going on and how do I apply this to my work?
===================================================

Everything is drawn in to a framebuffer object, and the GL shader renders this data with some number of pixels missing vertically and horizontally.

Unfortunately, you can't adjust the OF window size after the gl context is set up in main.cpp, so in most cases, you must launch your app full screen, with the right size for all your monitors. For example, if you are working with a grid of 2x3 monitors at resolution 800x600, you must launch your app at 1600x1800.  

This addon performs no proportion compensation. (But frankly, for a small enough bezel, it's no big deal.)

A 500x700 debug image is provided. The debug image is helpful when determining the number of pixels to remove during compensation. If you work with a different total resolution, you must create a new debug image of that resolution. I suggest using diagonal lines, because it's easy to spot misalignments. Also, hearts and unicorns.

For some info on how to get your OF window to span multiple monitors, I suggest this thread: http://forum.openframeworks.cc/index.php/topic,693.0.html

An example of this out in the wild is "Sanctum" by James Coupe and Juan Pampin.
