#!/bin/sh
#
#    File:    geo-explore
#    Author:  Marvin Smith
#    Date:    5/30/2014
#

#  Find out where the executable is
BASE_PATH=`dirname $0`

#  Go to that directory
cd ${BASE_PATH}/../share/GeoExplore

./bin/geo-explore $@

