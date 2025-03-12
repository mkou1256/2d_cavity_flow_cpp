#ifndef DATA2D_HPP
#define DATA2D_HPP

#include <vector>
#include <iostream>
#include <stdexcept> // For std::invalid_argument

using data_2d = std::vector<std::vector<double>>;

class Data2D {
public:
    data_2d data;

    // Constructor
    Data2D(size_t rows, size_t cols, double init_val = 0.0);
    Data2D(const data_2d& d);

    // Get number of rows and columns
    size_t rows() const;
    size_t cols() const;

    // Element-wise addition
    Data2D operator+(const Data2D& other) const;

    // Element-wise multiplication
    Data2D operator*(const Data2D& other) const;

    // Transpose the matrix
    Data2D transpose() const;

    // Print matrix with (0,0) at the bottom-left
    void print() const;
};

#endif // DATA2D_HPP
