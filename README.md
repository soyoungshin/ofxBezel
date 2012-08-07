ofxBezel
========

An openframeworks addon to perform bezel compensation when displaying over multiple monitors in a grid-like fashion.

The amount of pixels removed between screens is adjustable on the fly, but the number of rows/columns of monitors used and screen resolution is set during setup, so it can't be adjusted on the fly.

Most of the work occurs within a GL shader, so it may not work on all hardware.
