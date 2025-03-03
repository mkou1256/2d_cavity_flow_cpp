#include "mesh2d.hpp"
#include "flow_field.hpp"
#include <iostream>
#include <fstream>

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

void FlowField::save_to_file(
    const std::string& filename,
    const std::string& format
) const {
    if (format == "csv"){
        write_csv(filename + "_u.csv", u);
        write_csv(filename + "_v.csv", v);
        write_csv(filename + "_p.csv", p);
    } else if(format == "bin"){
        write_binary(filename + "_u.bin", u);
        write_binary(filename + "_v.bin", v);
        write_binary(filename + "_p.bin", p);
    } else {
        std::cerr << "Unsupported format: " << format << std::endl;
    }
}

void FlowField::write_csv(
    const std::string& filename,
    const std::vector<std::vector<double>>& data
) const {
    std::ofstream file(filename);
    if (!file){
        std::cerr << "[Error] Could not open file "
            << filename << " for writing." << std::endl;
        return;
    }
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}

void FlowField::write_binary(
    const std::string& filename,
    const std::vector<std::vector<double>>& data
) const {
    std::ofstream file(filename);
    if (!file){
        std::cerr << "[Error] Could not open file "
            << filename << " for writing." << std::endl;
        return;
    }
    for (const auto& row : data) {
        file.write(
            reinterpret_cast<const char*>(row.data()), row.size()*sizeof(double)
        );
    }
    file.close();
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