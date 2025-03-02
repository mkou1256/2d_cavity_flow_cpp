#include "mesh2d.hpp"
#include <iostream>

Mesh2D::Mesh2D(int nx, int ny, double lx, double ly){
    //center of grids, xc and yc
    for (int i = 0; i < nx; ++i){
        xc.push_back((static_cast<double>(i) + 0.5) * (lx/nx));
    }
    for (int j = 0; j < ny; ++j){
        yc.push_back((static_cast<double>(j) + 0.5) * (ly/ny));
    }
    // edge of grids, for vector
    for (int i = 0; i <= nx; ++i){
        xu.push_back(static_cast<double>(i) * (lx/nx));
    }
    for (int j = 0; j <= ny; ++j){
        yv.push_back(static_cast<double>(j) * (ly/ny));
    }
}

const std::vector<double>& Mesh2D::getXc() const { return xc; }
const std::vector<double>& Mesh2D::getYc() const { return yc; }
const std::vector<double>& Mesh2D::getXu() const { return xu; }
const std::vector<double>& Mesh2D::getYv() const { return yv; }

// for debug
void Mesh2D::print() const {
    std::cout << "xc: " ;
    for (double xi : xc){
        std::cout << xi << " ";
    }
    std::cout << std::endl; 

    std::cout << "yc: " ;
    for (double yi : yc){
        std::cout << yi << " ";
    }
    std::cout << std::endl; 

    std::cout << "xu: " ;
    for (double xi : xu){
        std::cout << xi << " ";
    }
    std::cout << std::endl; 

    std::cout << "yv: " ;
    for (double yi : yv){
        std::cout << yi << " ";
    }
    std::cout << std::endl; 
}