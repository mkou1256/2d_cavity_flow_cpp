#ifndef DATA2D_HPP
#define DATA2D_HPP

#include <vector>
#include <iostream>
#include <stdexcept> // For std::invalid_argument


class Data2D {
public:
    std::vector<std::vector<double>> data;

    // Constructor
    Data2D(size_t rows, size_t cols, double init_val = 0.0);
    Data2D(const std::vector<std::vector<double>>& d);

    // Get number of rows and columns
    size_t rows() const;
    size_t cols() const;

    // index access like python
    const double& operator()(size_t i, size_t j) const;

    // slice operator
    std::vector<double> operator()(size_t row, All) const;
    std::vector<double> operator()(All, size_t col) const;

    // Element-wise addition
    Data2D operator+(const Data2D& other) const;

    // Element-wise multiplication
    Data2D operator*(const Data2D& other) const;

    // Transpose the matrix
    Data2D transpose() const;

    // Print matrix with (0,0) at the bottom-left
    void print() const;
};


// for slice
struct All {};
constexpr All all{};

#endif // DATA2D_HPP
