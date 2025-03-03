#include "mesh2d.hpp"
#include "flow_field.hpp"
#include <iostream>

int main() {
    int nx = 8, ny = 8;
    double Lx = 1.0, Ly = 1.0;

    Mesh2D mesh(nx, ny, Lx, Ly);
    mesh.print();

    FlowField field(mesh);

    std::vector<std::vector<double>> du(nx+1, std::vector<double>(ny  , 0.1));
    std::vector<std::vector<double>> dv(nx  , std::vector<double>(ny+1, 0.1));
    std::vector<std::vector<double>> dp(nx  , std::vector<double>(ny  , 0.1));

    std::cout << "Before update: " << std::endl;
    field.print();

    field.update(du, dv, dp);
    std::cout << "After update: " << std::endl;
    field.print();

    std::cout << "save to csv.\n";
    field.save_to_file("test", "csv");
    return 0;
}
