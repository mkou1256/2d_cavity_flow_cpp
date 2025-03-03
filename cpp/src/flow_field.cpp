#include "mesh2d.hpp"
#include "flow_field.hpp"
#include <iostream>

FlowField::FlowField(const Mesh2D& mesh)
    : nx(mesh.get_xc().size()), ny(mesh.get_yc().size()) {
    // extend number of grid and initialize with zero
    u.resize(nx+1, std::vector<double>(ny  , 0.0));
    v.resize(nx  , std::vector<double>(ny+1, 0.0));
    p.resize(nx  , std::vector<double>(ny  , 0.0));
}

void FlowField::update(
    const std::vector<std::vector<double>>& du,
    const std::vector<std::vector<double>>& dv,
    const std::vector<std::vector<double>>& dp
    ) {
    for (int i = 0; i <= nx; ++i) {
        for (int j = 0; j < ny; ++j){
            u[i][j] += du[i][j];
        }
    }
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j <= ny; ++j){
            v[i][j] += dv[i][j];
        }
    }
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j){
            p[i][j] += dp[i][j];
        }
    }
}

// for debug
void FlowField::print() const {
    std::cout << "u field:" << std::endl;
    for (const auto& row : u) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "v field:" << std::endl;
    for (const auto& row : v) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "p field:" << std::endl;
    for (const auto& row : p) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}