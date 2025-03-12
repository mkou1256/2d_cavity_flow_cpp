#include "data2d.hpp"

// Constructor: Initialize matrix with given rows and columns
Data2D::Data2D(size_t rows, size_t cols, double init_val) 
    : data(rows, std::vector<double>(cols, init_val)) {}

// Constructor: Initialize matrix from existing data
Data2D::Data2D(const data_2d& d) : data(d) {}

// Get the number of rows
size_t Data2D::rows() const { return data.size(); }

// Get the number of columns
size_t Data2D::cols() const { return data.empty() ? 0 : data[0].size(); }

// Element-wise addition
Data2D Data2D::operator+(const Data2D& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::invalid_argument("Data2D dimensions must match for addition.");
    }
    Data2D result(rows(), cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Element-wise multiplication
Data2D Data2D::operator*(const Data2D& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::invalid_argument("Data2D dimensions must match for element-wise multiplication.");
    }
    Data2D result(rows(), cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result.data[i][j] = data[i][j] * other.data[i][j];
        }
    }
    return result;
}

// Transpose the matrix
Data2D Data2D::transpose() const {
    if (data.empty()) return Data2D(0, 0);
    Data2D result(cols(), rows());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

// Print matrix with (0,0) at the bottom-left
void Data2D::print() const {
    for (int i = rows() - 1; i >= 0; --i) { // Print from top to bottom (reversed row order)
        for (size_t j = 0; j < cols(); ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}
