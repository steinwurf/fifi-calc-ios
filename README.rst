=========
fifi-calc
=========

Generate PNGs
=============
When creating an app you need to provide the images like the app icon in many different resolutions.
These can be generated using an SVG.
As of writing these sizes are required for the app icon:

  20, 29, 40, 58, 60, 76, 80, 87, 120, 152, 167, 180 px

MacOS
-----
For reasons unkown to me, the size of the svg means something on MacOS. If the SVG is too small it will be put on a canvas bigger than the image. To fix this scale the SVG in a tool like inkscape. I've found that a size of 1000 px on each side is sufficient.

The command for converting svg to png's is as follows:
 
  qlmanage -t -s [SIZE] -o . [SVG_FILE]
