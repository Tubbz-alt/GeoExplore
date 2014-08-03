#include <iostream>
#include <vector>

using namespace std;

/**
 * Compute Mesh Function
*/
void computeMesh( int const& sz_x, int const& sz_y, const int& tau, const std::vector<std::vector<double> >& z, double const& e, double const& r ){
    
    // Create zero matrix for initial active vertices
    std::vector<std::vector<bool> >  active_vertices(sz_y);
    for( int y=0; y<sz_y; y++ )
    for( int x=0; x<sz_x; x++ )
        active_vertices.push_back(false);

    // set corners and center to active by default
    active_vertices[    0     ][     0    ] = true;
    active_vertices[ sz_x -1  ][     0    ] = true;
    active_vertices[    0     ][ sz_y-1   ] = true;
    active_vertices[ sz_x-1   ][ sz_y-1   ] = true;
    active_vertices[(sz_x+1)/2][(sz_y+1)/2] = true;


}

int main( int argc, char* argv[] ){
    
    // 


    return 0;
}


