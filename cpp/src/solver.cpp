#include "solver.hpp"
#include <vector>
#include <cmath>

SMACSolver::SMACSolver(const Mesh2D& mesh, FlowField& flow_field, const DiffMethod& diff_method, double dt)
    : mesh(mesh), flow_field(flow_field), diff_method(diff_method), dt(dt) {}

std::vector<std::vector<double>> SMACSolver::interpolate_u_to_v(
    std::vector<std::vector<double>>& u,
    const Mesh2D& mesh
) const {
    // Interpolate u to v location
    int nx = mesh.get_xc().size();
    int ny = mesh.get_yc().size();
    std::vector<std::vector<double>> u_to_v(nx, std::vector<double>(ny+1, 0.0));
    for (int i = 0; i < nx; ++i) {
        u_to_v[i][0] = 0.0; // Boundary condition
        u_to_v[i][ny] = 0.0; // Boundary condition
        for (int j = 1; j < ny; ++j) {
            u_to_v[i][j] = 0.25 * (
                u[i][j] + u[i+1][j] + u[i][j-1] + u[i+1][j-1]
            );
        }
    }
    return u_to_v;
}

std::vector<std::vector<double>> SMACSolver::interpolate_v_to_u(
    std::vector<std::vector<double>>& v,
    const Mesh2D& mesh
) const {
    // Interpolate v to u location
    int nx = mesh.get_xc().size();
    int ny = mesh.get_yc().size();
    std::vector<std::vector<double>> v_to_u(nx, std::vector<double>(ny, 0.0));
    for (int i = 1; i < nx-1; ++i) {
        for (int j = 1; j < ny-1; ++j) {
            v_to_u[i][j] = 0.25 * (
                v[i-1][j+1] + v[i][j+1] + v[i-1][j] + v[i][j]
            );
        }
    }
    return v_to_u;
}

std::vector<std::vector<double>> SMACSolver::interpolate_p_to_u(
    std::vector<std::vector<double>>& p,
    const Mesh2D& mesh
) const {
    // Interpolate p to u location
    int nx = mesh.get_xc().size();
    int ny = mesh.get_yc().size();
    std::vector<std::vector<double>> p_to_u(nx, std::vector<double>(ny, 0.0));
    for (int i = 1; i < nx-1; ++i) {
        for (int j = 1; j < ny-1; ++j) {
            p_to_u[i][j] = 0.5 * (p[i][j] + p[i-1][j]);
        }
    }
    return p_to_u;
}

std::vector<std::vector<double>> SMACSolver::interpolate_p_to_v(
    std::vector<std::vector<double>>& p,
    const Mesh2D& mesh
) const {
    // Interpolate p to v location
    int nx = mesh.get_xc().size();
    int ny = mesh.get_yc().size();
    std::vector<std::vector<double>> p_to_v(nx, std::vector<double>(ny, 0.0));
    for (int i = 1; i < nx-1; ++i) {
        for (int j = 1; j < ny-1; ++j) {
            p_to_v[i][j] = 0.5 * (p[i][j] + p[i][j-1]);
        }
    }
    return p_to_v;
}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> SMACSolver::compute_advection_term(
    const std::vector<std::vector<double>>& u, 
    const std::vector<std::vector<double>>& v, 
    const std::vector<double>& xc, 
    const std::vector<double>& yc
) const {
    int nx = xc.size();
    int ny = yc.size();
    std::vector<std::vector<double>> advection_term_u(nx, std::vector<double>(ny, 0.0));
    std::vector<std::vector<double>> advection_term_v(nx, std::vector<double>(ny, 0.0));

    for (int i = 1; i < nx-1; ++i) {
        for (int j = 1; j < ny-1; ++j) {
            double du_dx = diff_method.compute(u[i], xc)[j];
            double du_dy = diff_method.compute(u[j], yc)[i];
            double dv_dx = diff_method.compute(v[i], xc)[j];
            double dv_dy = diff_method.compute(v[j], yc)[i];
            double u_ij = u[i][j];
            double v_ij = v[i][j];
            advection_term_u[i][j] = u_ij * du_dx + v_ij * du_dy;
            advection_term_v[i][j] = u_ij * dv_dx + v_ij * dv_dy;
        }
    }
    return {advection_term_u, advection_term_v};
}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> SMACSolver::compute_pressure_term(
    const std::vector<std::vector<double>>& p, 
    const std::vector<double>& xc, 
    const std::vector<double>& yc
) const {
    int nx = xc.size();
    int ny = yc.size();
    std::vector<std::vector<double>> pressure_term_u(nx, std::vector<double>(ny, 0.0));
    std::vector<std::vector<double>> pressure_term_v(nx, std::vector<double>(ny, 0.0));

    for (int i = 1; i < nx-1; ++i) {
        for (int j = 1; j < ny-1; ++j) {
            std::vector<double> p_x = p[i];
            std::vector<double> p_y(ny);
            for (int k = 0; k < ny; ++k) {
                p_y[k] = p[k][j];
            }
            pressure_term_u[i][j] = diff_method.compute(p_x, xc)[j];
            pressure_term_v[i][j] = diff_method.compute(p_y, yc)[i];
        }
    }
    return {pressure_term_u, pressure_term_v};
}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> SMACSolver::compute_viscosity_term(
    const std::vector<std::vector<double>>& u, 
    const std::vector<double>& xc, 
    const std::vector<double>& yc
) const {
    int nx = xc.size();
    int ny = yc.size();
    std::vector<std::vector<double>> viscosity_term_u(nx, std::vector<double>(ny, 0.0));
    std::vector<std::vector<double>> viscosity_term_v(nx, std::vector<double>(ny, 0.0));

    for (int i = 1; i < nx-1; ++i) {
        for (int j = 1; j < ny-1; ++j) {
            std::vector<double> u_x = u[i];
            std::vector<double> u_y(ny);
            for (int k = 0; k < ny; ++k) {
                u_y[k] = u[k][j];
            }
            double d2u_dx2 = diff_method.compute(diff_method.compute(u_x, xc), xc)[j];
            double d2u_dy2 = diff_method.compute(diff_method.compute(u_y, yc), yc)[i];
            viscosity_term_u[i][j] = d2u_dx2 + d2u_dy2;

            std::vector<double> v_x = u[i];
            std::vector<double> v_y(ny);
            for (int k = 0; k < ny; ++k) {
                v_y[k] = u[k][j];
            }
            double d2v_dx2 = diff_method.compute(diff_method.compute(v_x, xc), xc)[j];
            double d2v_dy2 = diff_method.compute(diff_method.compute(v_y, yc), yc)[i];
            viscosity_term_v[i][j] = d2v_dx2 + d2v_dy2;
        }
    }
    return {viscosity_term_u, viscosity_term_v};
}

void SMACSolver::compute_intermediate_velocity() {
    // Compute intermediate velocities u* and v*
    int nx = mesh.get_xc().size();
    int ny = mesh.get_yc().size();
    std::vector<std::vector<double>> du(nx+1, std::vector<double>(ny, 0.0));
    std::vector<std::vector<double>> dv(nx, std::vector<double>(ny+1, 0.0));

    auto [advection_term_u, advection_term_v] = compute_advection_term(flow_field.get_u(), flow_field.get_v(), mesh.get_xu(), mesh.get_yc());
    auto [pressure_term_u, pressure_term_v] = compute_pressure_term(flow_field.get_p(), mesh.get_xc(), mesh.get_yc());
    auto [viscosity_term_u, viscosity_term_v] = compute_viscosity_term(flow_field.get_u(), mesh.get_xc(), mesh.get_yc());

    for (int i = 1; i < nx-1; ++i) {
        for (int j = 1; j < ny-1; ++j) {
            du[i][j] = dt * (advection_term_u[i][j] + pressure_term_u[i][j] + viscosity_term_u[i][j]);
            dv[i][j] = dt * (advection_term_v[i][j] + pressure_term_v[i][j] + viscosity_term_v[i][j]);
        }
    }
    std::vector<std::vector<double>> zero_p(nx, std::vector<double>(ny, 0.0));
    flow_field.update(du, dv, zero_p); // intermediate velocity update
}

void SMACSolver::solve_pressure_poisson() {
    // Solve the pressure Poisson equation
    int nx = mesh.get_xc().size();
    int ny = mesh.get_yc().size();
    std::vector<std::vector<double>> p_new = flow_field.get_p();

    for (int iter = 0; iter < 100; ++iter) { // Number of iterations can be adjusted
        for (int i = 1; i < nx-1; ++i) {
            for (int j = 1; j < ny-1; ++j) {
                double rhs = (flow_field.get_u()[i+1][j] - flow_field.get_u()[i-1][j]) / (2.0 * mesh.get_dx()) +
                             (flow_field.get_v()[i][j+1] - flow_field.get_v()[i][j-1]) / (2.0 * mesh.get_dy());
                p_new[i][j] = (1.0 / (2.0 / (mesh.get_dx() * mesh.get_dx()) + 2.0 / (mesh.get_dy() * mesh.get_dy()))) *
                              ((flow_field.get_p()[i+1][j] + flow_field.get_p()[i-1][j]) / (mesh.get_dx() * mesh.get_dx()) +
                               (flow_field.get_p()[i][j+1] + flow_field.get_p()[i][j-1]) / (mesh.get_dy() * mesh.get_dy()) -
                               rhs);
            }
        }
        flow_field.update(flow_field.get_u(), flow_field.get_v(), p_new);
    }
}

void SMACSolver::update_velocity() {
    // Update velocities u and v using the pressure field
    int nx = mesh.get_xc().size();
    int ny = mesh.get_yc().size();
    std::vector<std::vector<double>> u_new = flow_field.get_u();
    std::vector<std::vector<double>> v_new = flow_field.get_v();

    for (int i = 1; i < nx-1; ++i) {
        for (int j = 1; j < ny-1; ++j) {
            double dp_dx = (flow_field.get_p()[i+1][j] - flow_field.get_p()[i-1][j]) / (2.0 * mesh.get_dx());
            double dp_dy = (flow_field.get_p()[i][j+1] - flow_field.get_p()[i][j-1]) / (2.0 * mesh.get_dy());
            u_new[i][j] = flow_field.get_u()[i][j] - dt * dp_dx;
            v_new[i][j] = flow_field.get_v()[i][j] - dt * dp_dy;
        }
    }

    flow_field.update(u_new, v_new, flow_field.get_p());
}

void SMACSolver::step() {
    compute_intermediate_velocity();
    solve_pressure_poisson();
    update_velocity();
}