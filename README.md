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

### Apps ###

In order to test the API, we are writing a series of applications to serve as useful utilities.

#### geo-convert ####

Perform Coordinate conversions and Image conversion.

Coordinate Conversion
    
    geo-convert -c -i -geo-dd:39:-120:0:WGS84 -o -utm

Raster Conversion
    
    geo-convert -r -i image.jpg -o image.png

#### geo-info ####

Extract information from the input source.

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


### IO Module ###

In order to handle Input/Output for GeoExplore, a number of drivers have been implemented.  Currently the drivers 
are hacked together in the ImageIO and OGR Driver modules, but eventually, I will create a cohesive standard for 
implementing drivers.

####  Supported Drivers ####

* Geospatial Data Abstraction Library (GDAL - Image/DEM, OGR - Coordinate)
* OpenCV - Image IO
* NETPBM - Image write (I am writing this as a standard driver model)


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

