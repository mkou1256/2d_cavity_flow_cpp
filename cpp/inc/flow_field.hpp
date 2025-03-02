#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "mesh2d.hpp"

class FlowField {
    private:
        int nx, ny;
        std::vector<std::vector<double>> u, v, p;
    
    public:
        FlowField(const Mesh2D& mesh);

        void update(
            const std::vector<std::vector<double>>& du,
            const std::vector<std::vector<double>>& dv,
            const std::vector<std::vector<double>>& dp
        );

        const std::vector<std::vector<double>>& get_u() const;
        const std::vector<std::vector<double>>& get_v() const;
        const std::vector<std::vector<double>>& get_p() const;

        //for debug
        void print() const;
};




#endif //FIELD_H