#!/bin/sh
#
#    File:    geo-convert-test.sh
#    Author:  Marvin Smith
#    Date:    5/6/2014
#
#    Purpose: Unit tests for geo-convert
#



#  Run application converting UTM to Geodetic DD
echo 'Testing UTM to Geodetic-DD'
./release/bin/geo-convert -c -i -utm:18:323394:4307396 -o -geod-dd


#  Convert Geodetic DD to UTM
echo 'Testing Geodetic-DD to UTM'
./release/bin/geo-convert -c -i -geod-dd:38.8977:-77.0365 -o -utm


