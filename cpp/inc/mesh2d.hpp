#ifndef MESH2D_H
#define MESH2D_H

#include <vector>

class Mesh2D{
    private:
        int nx, ny; // number of grids
        int n_ghost_cells; // number of ghost cells
        double lx, ly; // length of domain
        std::vector<double> xc, yc; // center of grids, for scaler
        std::vector<double> xu, yv; // edge of grids, for vector
    
    public:
        Mesh2D(int nx, int ny, double lx, double ly, int n_ghost_cells = 1);

        const std::vector<double>& get_xc() const;
        const std::vector<double>& get_yc() const;
        const std::vector<double>& get_xu() const;
        const std::vector<double>& get_yv() const;

        void print() const;
};

#endif // MESH2D_H