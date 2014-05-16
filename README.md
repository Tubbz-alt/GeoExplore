GeoExplore
==========

Overview
--------

GeoExplore is a GIS Library which provides useful utilities for conducting research
and analysis of geo-spatial information. In addition, we are currently working on a
3D mapping server which will allow clients to view image data in 3D provided appropriate 
elevation data exists. 

Modules
-------


### Coordinate Module ###

The coordinate module contains various utilities and classes to enable conversions between common 
geographical coordinate systems and types.  Below is a list of the current supported systems.
More systems will be added as the project matures.

#### Datums ####
* WGS84
* NAD83

#### Coordinate Types ####
* UTM (Universal Transverse Mercator)
* Geodetic (Latitude/Longitude)


### Image Module ###

GeoExplore contains an image module which allows users to read, manipulate, and write images.

The basic usage of the module is as such for an image loaded into memory.

    Image<PixelRGB_u8> image;
    load_image( "foo.jpg", image );

Another module still being designed is the DiskImage class which uses lazy evaluation in conjunction with a
read-only driver to handle larger and less robust image files.

    Image<PixelGray_d> image;
    load_image( "foo.tif", image );

Both of these classes are based on the same Image\_ class, but vary on the resource type used
to store the pixel data.  MemoryResource stores the data locally in contiguous memory like an array. 
The DiskResource stores the driver, which has the data needed to open the data and pass it when referenced.
<!---
Implementation for the DiskResource differs by 
--->

Building GeoExplore
-------------------

# Linux #

From the command-line in the base project directory, run...

    ./build.sh -m 

To install, type...
    
    ./build.sh -i

To customize the installation, run the script to see available options.

    ./build.sh -h

To run unit tests, run the script

    ./build.sh -t

To see examples of using GeoExplore binaries, see the items in scripts.

TODO
====

Needed Unit Tests
-----------------

* UTM to UTM: change only Datum
* UTM to UTM: change only zone
* UTM to UTM: change both DATUM and Zone
* UTM to UTM: change nothing, make sure output returns input 

* UTM to Geod: same datum
* UTM to Geod: different datum

* Geodetic to UTM: same datum, free zone
* Geodetic to UTM: same datum, fixed zone
* Geodetic to UTM: different datum, free zone
* Geodetic to UTM: different datum, fixed zone

* Geodetic to Geodetic: same datum, make sure output returns input
* Geodetic to Geodetic: different datum

