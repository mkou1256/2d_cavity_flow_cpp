#include "diff.hpp"
#include <iostream>

std::vector<double> SecondOrderCenterDiff::compute(
    const std::vector<double>& f, const std::vector<double>& x
) const {
    size_t n = f.size();
    if (n != x.size()) {
        std::cerr << "[Error] Invalid size of vector.\n";
        return std::vector<double>(); //return empty vector when error.
    }

    std::vector<double> df_dx(n, 0.0);
    df_dx[0] = (f[1] - f[0]) / (x[1] - x[0]); // for i = 0 boundary
    for (size_t i = 1; i < n-1; ++i) {
        df_dx[i] = (f[i+1] - f[i-1]) / (x[i+1] - x[i-1]);
    }
    df_dx[n-1] = (f[n-1] - f[n-2]) / (x[n-1] - x[n-2]);  // for i = n-1 boundary

    return df_dx;
}