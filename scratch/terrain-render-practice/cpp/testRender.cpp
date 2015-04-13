
// C++ Standard Libraries
#include <cmath>
#include <iostream>
#include <vector>

// OpenCV Library
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;


Mat gensinc( const int& mesh_size, 
             const double& alpha )
{

    // Create x, y matrices
    Mat x(mesh_size, mesh_size, CV_64FC1);
    Mat y(mesh_size, mesh_size, CV_64FC1);

    for( int i=0; i<mesh_size-1; i++ ){
    for( int j=0; j<mesh_size-1; j++ ){
        x.at<double>(i,j) = j;
        y.at<double>(i,j) = i;
    }}

    //r = sqrt((x-(sz-1)/2).^2+(y-(sz-1)/2).^2);
    Mat r = x.clone();
    double tx, ty;
    for( int i=0; i<mesh_size-1; i++ ){
    for( int j=0; j<mesh_size-1; j++ ){
        tx = x.at<double>(i,j)-(mesh_size/2);
        ty = y.at<double>(i,j)-(mesh_size/2);
        r.at<double>(i,j) = sqrt(tx*tx + ty*ty);
    }}

    //z = sin(r*16/(sz-1)*2)./(r*16/(sz-1)*2);
    Mat output = r.clone();
    double r16;
    for( int i=0; i<mesh_size-1; i++ )
    for( int j=0; j<mesh_size-1; j++ ){
        r16 = r.at<double>(i,j) * 16;
        output.at<double>(i,j) = (sin(r16/(mesh_size-1)*2)/(r16 / (mesh_size-1)*2)) * alpha;
    }
  
    return output;
}

void initValues( const int& mesh_size ){



}


int main( int argc, char* argv[] ){
   
    // mesh size
    int mesh_size = 20;
    double alpha = 100;

    // Generate sinc function
    Mat z = gensinc( mesh_size, alpha );

    // Perform Pre-Processing on Data
    std::cout << z << std::endl;

    return 0;
}


