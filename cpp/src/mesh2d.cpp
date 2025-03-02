#include "mesh2d.hpp"
#include <iostream>

Mesh2D::Mesh2D(int nx, int ny, double lx, double ly){
    //center of grids, xc and yc
    for (int i = 0; i < nx; ++i){
        xc.push_back(lx);
    }
}