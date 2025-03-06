#include "diff.hpp"
#include <iostream>
#include <cmath>


void print_vector(const std::vector<double>& vec) {
    for (double v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

int main() {
    // テスト範囲
    double xmin = 0.0;
    double xmax = 2.0 * M_PI;
    int N = 100;
    double dx = (xmax - xmin) / (N - 1);

    // x座標の設定
    std::vector<double> x(N);
    for (int i = 0; i < N; ++i) {
        x[i] = xmin + i * dx;
    }

    // f(x) = sin(x) のデータを生成
    std::vector<double> f(N);
    for (int i = 0; i < N; ++i) {
        f[i] = std::sin(x[i]);
    }

    // 差分法の適用
    SecondOrderCenterDiff diff_method;
    std::vector<double> df = diff_method.compute(f, x);

    // 理論的な cos(x) の値と比較
    //std::cout << "Numerical Derivative (df/dx):" << std::endl;
    //print_vector(df);

    //std::cout << "Analytical cos(x):" << std::endl;
    std::vector<double> analytical(N);
    for (int i = 0; i < N; ++i) {
        analytical[i] = std::cos(x[i]);
    }
    //print_vector(analytical);

    // compute RMSE
    double rmse = 0.0;
    for (int i = 0; i < N; ++i){
        rmse += (df[i] - analytical[i])*(df[i] - analytical[i]);
    }
    rmse /= N;
    std::cout << "RMSE = " << rmse << std::endl;

    return 0;
}