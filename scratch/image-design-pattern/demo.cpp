#include <iostream>

#include "Design.hpp"

using namespace std;

int main( int argc, char* argv[] ){

    /// Create a ram-based image
    cout << "Creating Image<PixelRGB_u8> image01" << endl;
    Image<PixelRGB_u8> image01;
    cout << "Finished creating image01" << endl;
    cout << endl;
    
    
    /// Create a disk image
    cout << "Creating DiskImage<PixelGray_d> image02" << endl;
    DiskImage<PixelGray_d> image02;
    cout << "Finished creating image02" << endl;

    /// Create an Ortho Image
    cout << "Creating OrthoImage<PixelGray_u12> image03" << endl;
    OrthoImage<PixelGray_d> image03;

    /// Create an Ortho Disk Image
    cout << "Creating OrthoDiskImage<PixelRGB_u16> image04" << endl;
    OrthoDiskImage<PixelRGB_u16> image04;

}

