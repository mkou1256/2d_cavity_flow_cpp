#ifndef FIELD_H
#define FIELD_H

#include "mesh2d.hpp"
#include <vector>
#include <string>

class FlowField {
    private:
        int nx, ny;
        std::vector<std::vector<double>> u, v, p;

        void write_csv(
            const std::string& filename,
            const std::vector<std::vector<double>>& data
        ) const;
        void write_binary(
            const std::string& filename,
            const std::vector<std::vector<double>>& data
        ) const;
        
    public:
        FlowField(const Mesh2D& mesh);

        void update(
            const std::vector<std::vector<double>>& du,
            const std::vector<std::vector<double>>& dv,
            const std::vector<std::vector<double>>& dp
        );

        void boundary_condition();

        void save_to_file(
            const std::string& filename,
            const std::string& format = "csv"
        ) const;

        const std::vector<std::vector<double>>& get_u() const;
        const std::vector<std::vector<double>>& get_v() const;
        const std::vector<std::vector<double>>& get_p() const;

        //for debug
        void print() const;
};




#endif //FIELD_H