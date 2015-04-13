#    File:    FindGeoExplore.cmake
#    Author:  Marvin Smith
#    Date:    4/11/2015
#
#    Purpose: Helps third-party applications find GeoExplore builds
#
#
# - Config file for the GeoExplore package
# It defines the following variables
#
#  GeoExplore_INCLUDE_DIR - Path to the Header Files.
#  GeoExplore_LIBRARIES   - Path to the Libraries.
#  GeoExplore_FOUND       - Set if found.
#
#  Notes:
#    -  If GeoExplore is not installed to a system area, or if you want to
#       point your project to a checkout of the GeoExplore repository, then
#       set an environment variable to GeoExplore_BASE and CMake should find it.
#

#  Print Entry
message("Configuring GeoExplore")

#  Check for an environment variable
if( EXISTS $ENV{GeoExplore_BASE} )

    #  Search for the header path
    set( GeoExplore_INCLUDE_DIR "$ENV{GeoExplore_BASE}/src/lib")

    #  Search for the library
    find_library( GeoExplore_LIBRARY 
                    NAMES
                        GeoExplore
                    HINTS
                        "$ENV{GeoExplore_BASE}/lib"
                        "$ENV{GeoExplore_BASE}/release/lib"
                        "$ENV{GeoExplore_BASE}/debug/lib"
    )
    if( GeoExplore_LIBRARY )
        list( APPEND GeoExplore_LIBRARIES ${GeoExplore_LIBRARY})
    endif()
    
    #  Set to found
    if( GeoExplore_LIBRARIES )
        message("Found GeoExplore")
        message("GeoExplore Includes  : ${GeoExplore_INCLUDE_DIR}")
        message("GeoExplore Libraries : ${GeoExplore_LIBRARIES}")
        set( GeoExplore_FOUND TRUE )
    endif()

#  If no Environment Variable found, look for the components
else()

    #  Otherwise, we have a problem
    message("GeoExplore Not Found.")

endif()

