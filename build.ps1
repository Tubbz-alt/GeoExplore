#    File: build.ps1
#    Author:  Marvin Smith
#    Date:    5/10/2014
#
#    Purpose:  Build script for Microsoft Visual Studio
#
Param(
    [Parameter(Mandatory=$False)][switch]$Make,
    [Parameter(Mandatory=$False)][string]$BuildType
)

#--------------------------------#
#-       Global Variables       -#
#--------------------------------#
$global:gdal_library_path='/opt/gdal/bin/gdal.dll'
$global:gdal_include_path='/opt/gdal/include/gdal'

$global:opencv_dir='/opt/opencv/lib'

#---------------------------------------------------#
#-        Read the XML Configuration File          -#
#---------------------------------------------------#
Function read_configuration_file(){
    Param(
        [parameter(Mandatory=$true)][string]$ConfigurationFilename
    )

    #  Open the XML File
    $config = [xml](Get-Content $ConfigurationFilename)
    
    #  Extract GDAL Parameters
    $global:gdal_library_path=$config.configuration.gdal.library
    $global:gdal_include_path=$config.configuration.gdal.include
    
    #  Extract OpenCV Parameters
    $global:opencv_dir=$config.configuration.opencv.cmake
    

}

#---------------------------------------------------------#
#-        Build the Required Directory Structure         -#
#---------------------------------------------------------#
Function create-directory-structure(){

    Param(
        [parameter(Mandatory=$true)][string]$BuildDirectory
    )

    #  Create the base path
    if( $(Test-Path -Path $BuildDirectory) -ne $true ){
        New-Item -Path $BuildDirectory -ItemType directory
    }

    #  Create the lib path
    if( $(Test-Path -Path "$BuildDirectory\bin") -ne $true ){
        New-Item -Path "$BuildDirectory\bin" -ItemType directory
    }

}

#------------------------------------------------#
#-        Build the GeoExplore software         -#
#------------------------------------------------#
Function build_software( ){
    Param(
        [parameter(Mandatory=$true)][string]$BuildDirectory
    )

    #  Print header
    Write-Host -ForegroundColor Green '-> building software.'
    Write-Host -ForegroundColor Green "   Path: $BuildDirectory"
    Write-Host -ForegroundColor Green ''

    #  Create directory structure
    create-directory-structure -BuildDirectory $BuildDirectory

    #  Enter the directory
    cd $BuildDirectory

    #  Run CMake
    cmake.exe ../install/lib -DGDAL_INCLUDE_DIR=$global:gdal_include_path -DGDAL_LIBRARY=$global:gdal_library_path -DOpenCV_DIR=$global:opencv_dir
    echo "cmake.exe ../install/lib -DGDAL_INCLUDE_DIR=$global:gdal_include_path -DGDAL_LIBRARY=$global:gdal_library_path"


    #  Exit
    cd ..
}


#  Read configuration file
read_configuration_file -ConfigurationFilename 'install\build-win64.xml'


#  Parse flags

#  if we are building, then run CMake
if( $Make -eq $true ){
    if( $BuildType -eq 'debug' ){
        build_software -BuildDirectory 'debug'
    }
    elseif( $BuildType -eq 'release' -or $BuildType -eq '' ){
        build_software -BuildDirectory 'release'
    }
}
