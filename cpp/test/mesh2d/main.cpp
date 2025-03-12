#include "mesh2d.hpp"
#include <iostream>

int main() {
    int nx = 8, ny = 8;        // 4×4 のセル
    double Lx = 1.0, Ly = 1.0; // 計算領域のサイズ

    Mesh2D mesh(nx, ny, Lx, Ly);
    
    // メッシュを表示
    mesh.print();
    int _nx = mesh.get_nx();
    int _ny = mesh.get_ny();
    std::cout << "nx, ny = " << _nx << ", " << _ny << std::endl;

    std::cout << "test for getXc()" << std::endl;
    std::vector<double> xc = mesh.get_xc();
    for (double xi : xc){
        std::cout << xi << " " ;
    }
    std::cout << std::endl;

    // try to update
    std::cout << "Original xc[0]: " << xc[0] << std::endl;
    xc[0] = 10.0;
    std::cout << "After xc[0] = 10: " << xc[0] << std::endl;
    std::cout << "mesh.print()" << std::endl;
    mesh.print();
    return 0;
}
