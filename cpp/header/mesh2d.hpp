#ifndef MESH2D_H
#define MESH2D_H

#include <vector>

class Mesh2D{
    private:
        int nx, ny; // number of grids
        double lx, ly; // length of domain
        std::vector<double> xc, yc; // center of grids, for scaler
        std::vector<double> xu, yv; // edge of grids, for vector
    
    public:
        Mesh2D(int nx, int ny, double lx, double ly);

        const std::vector<double>& getXc() const;
        const std::vector<double>& getYc() const;
        const std::vector<double>& getXu() const;
        const std::vector<double>& getYv() const;

        void print() const;
};

#endif // MESH2D_H