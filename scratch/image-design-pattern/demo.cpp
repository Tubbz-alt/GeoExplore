#include <iostream>

#include "Design.hpp"

using namespace std;

int main( int argc, char* argv[] ){

    /// Create a ram-based image
    cout << "Creating Image<PixelRGB_u8> image01" << endl;
    Image<PixelRGB_u8> image01;
    cout << "Finished creating image01" << endl;
    cout << "-> size: " << image01.rows() << " x " << image01.cols() << endl;
    cout << endl;
    
    
    /// Create a disk image
    cout << "Creating DiskImage<PixelGray_d> image02" << endl;
    DiskImage<PixelGray_d> image02;
    cout << "Finished creating image02" << endl;
    cout << "-> size: " << image02.rows() << " x " << image02.cols() << endl;
    cout << endl;

    /// Create an Ortho Image
    cout << "Creating OrthoImage<PixelGray_u12> image03" << endl;
    OrthoImage<PixelGray_d> image03;
    cout << "Finished creating image03" << endl;
    cout << "-> size: " << image03.rows() << " x " << image03.cols() << endl;
    cout << endl;

    /// Create an Ortho Disk Image
    cout << "Creating OrthoDiskImage<PixelRGB_u16> image04" << endl;
    OrthoDiskImage<PixelRGB_u16> image04;
    cout << "Finished creating image04" << endl;
    cout << "-> size: " << image04.rows() << " x " << image04.cols() << endl;
    image04.pixel2world();
    cout << endl;


    // the benefit of this is that you won't be able to set types against each other
    // as they are all separate types
    /**
     * Uncomment the section below to test compilation 
    *
    Image<PixelRGB_u8>  i1;
    Image<PixelRGB_d>   i2;
    Image<PixelGray_u8> i3;

    i1 = i3;
    i1 = i2;
    */


    return 0;
}

