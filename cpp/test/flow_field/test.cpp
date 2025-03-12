#include "mesh2d.hpp"
#include "flow_field.hpp"
#include <iostream>

int main() {
    int nx = 4, ny = 8;
    double Lx = 0.5, Ly = 1.0;

    Mesh2D mesh(nx, ny, Lx, Ly);
    mesh.print();

    FlowField field(mesh);

    std::vector<std::vector<double>> du(nx+1, std::vector<double>(ny+2, 0.1));
    std::vector<std::vector<double>> dv(nx+2, std::vector<double>(ny+1, 0.1));
    std::vector<std::vector<double>> dp(nx+2, std::vector<double>(ny+2, 0.1));

    std::cout << "Before update: " << std::endl;
    field.print();

    field.update(du, dv, dp);
    field.boundary_condition();
    std::cout << "After update: " << std::endl;
    field.print();

    std::cout << "save to csv.\n";
    field.save_to_file("test", "csv");
    std::cout << "save to bin.\n";
    field.save_to_file("test", "bin");

    std::vector<std::vector<double>> u(nx+1, std::vector<double>(ny+2, 0.0));
    std::vector<std::vector<double>> u_t(ny+2, std::vector<double>(nx+1, 0.0));
    u = field.get_u();
    std::cout << "u[0] = ";
    for (auto ui : u[0]) {
        std::cout << ui << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < ny+2; ++i) {
        for (int j = 0; j < nx+1; ++j) {
            u_t[i][j] = u[j][i];
        }
    }
    std::cout << "u_t[0] = ";
    for (auto ui : u_t[0]) {
        std::cout << ui << " ";
    }
    std::cout << std::endl;

    return 0;
}
