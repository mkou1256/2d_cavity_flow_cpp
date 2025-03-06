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
    df_dx[0] = (-3*f[0] + 4*f[1] - f[2]) / (x[2] - x[0]); // for i = 0 boundary, 2nd-order forward
    for (size_t i = 1; i < n-1; ++i) {
        df_dx[i] = (f[i+1] - f[i-1]) / (x[i+1] - x[i-1]); // 2nd-order central
    }
    df_dx[n-1] = (3*f[n-1] - 4*f[n-2] + f[n-3]) / (x[n-1] - x[n-3]);  // for i = n-1 boundary, 2nd-order backward

    return df_dx;
}