#!/bin/sh
#
#    File:     geo-convert-demo.sh
#    Author:   Marvin Smith
#    Date:     4/16/2014
#
#    Purpose:  Show how to use geo-convert.
#

# Example of coordinate-conversion from utm to geodetic decimal degrees
./release/bin/geo-convert -c -i -utm:18:323394:4307396 -o -geod-dd

# Example of coordinate-conversion from geodetic decimal degrees to utm
./release/bin/geo-convert -c -i -geod-dd:38.8977:-77.0365 -o -utm

# Example of image-conversion from NITF to PNG
./release/bin/geo-convert -r -i tests/data/images/i_3001a.ntf -o output.png

