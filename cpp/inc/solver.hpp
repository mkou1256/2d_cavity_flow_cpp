#ifndef SMAC_SOLVER_HPP
#define SMAC_SOLVER_HPP

#include "mesh2d.hpp"
#include "flow_field.hpp"
#include "diff.hpp"

class SMACSolver {
    private:
        const Mesh2D& mesh;
        FlowField& flow_field;
        const DiffMethod& diff_method;
        double dt;

        // Interpolation functions
        std::vector<std::vector<double>> interpolate_u_to_v(
            std::vector<std::vector<double>>& u,
            const Mesh2D& mesh
        ) const;
        std::vector<std::vector<double>> interpolate_v_to_u(
            std::vector<std::vector<double>>& v,
            const Mesh2D& mesh
        ) const;
        std::vector<std::vector<double>> interpolate_p_to_v(
            std::vector<std::vector<double>>& p,
            const Mesh2D& mesh
        ) const;
        std::vector<std::vector<double>> interpolate_p_to_u(
            std::vector<std::vector<double>>& p,
            const Mesh2D& mesh
        ) const;

        // Time-stepping functions
        void compute_intermediate_velocity();
        void solve_pressure_poisson();
        void update_velocity();

        // Term calculation functions, used in compute_intermediate_velocity()
        std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> 
        compute_advection_term(
            std::vector<std::vector<double>>& u,
            std::vector<std::vector<double>>& v,
            const Mesh2D& mesh,
            const DiffMethod& diff_method
        ) const;
        std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>
         compute_pressure_term(
            std::vector<std::vector<double>>& p,
            const Mesh2D& mesh,
            const DiffMethod& diff_method
        ) const;
        std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>
        compute_viscosity_term(
            std::vector<std::vector<double>>& u,
            std::vector<std::vector<double>>& v,
            const Mesh2D& mesh,
            const DiffMethod& diff_method
        ) const;

    public:
        SMACSolver(const Mesh2D& mesh, FlowField& flow_field, const DiffMethod& diff_method, double dt);

        void step();
};

#endif // SMAC_SOLVER_HPP