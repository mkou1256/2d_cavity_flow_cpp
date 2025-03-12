#include "data2d.hpp"
#include <cassert> // For testing

int main() {
    // ====== Constructor Tests ======

    // Test 1: Initialize with specific values
    Data2D A({{1, 2, 3}, {4, 5, 6}});
    Data2D B({{2, 3, 4}, {5, 6, 7}});

    // Test 2: Check rows and columns
    assert(A.rows() == 2);
    assert(A.cols() == 3);
    assert(B.rows() == 2);
    assert(B.cols() == 3);

    std::cout << "Matrix A:\n";
    A.print();
    std::cout << "\nMatrix B:\n";
    B.print();

    // ====== Arithmetic Operation Tests ======

    // Test 3: Element-wise addition
    Data2D C = A + B;
    std::cout << "\nA + B:\n";
    C.print();

    // Test 4: Element-wise multiplication
    Data2D D = A * B;
    std::cout << "\nA * B (Element-wise multiplication):\n";
    D.print();

    // Test 5: Transpose
    std::cout << "\nTranspose of A:\n";
    Data2D At = A.transpose();
    At.print();

    // ====== Constructor with rows, cols, init_val ======

    // Test 6: Initialize matrix with default value
    Data2D E(3, 4, 7.5);
    assert(E.rows() == 3);
    assert(E.cols() == 4);

    std::cout << "\nMatrix E (3x4, initialized with 7.5):\n";
    E.print();

    // Test 7: Check if all elements in E are initialized to 7.5
    for (size_t i = 0; i < E.rows(); ++i) {
        for (size_t j = 0; j < E.cols(); ++j) {
            assert(E.data[i][j] == 7.5);
        }
    }

    // Test 8: Create a zero matrix and check values
    Data2D F(2, 3, 0.0);
    assert(F.rows() == 2);
    assert(F.cols() == 3);

    std::cout << "\nMatrix F (2x3, initialized with 0.0):\n";
    F.print();

    for (size_t i = 0; i < F.rows(); ++i) {
        for (size_t j = 0; j < F.cols(); ++j) {
            assert(F.data[i][j] == 0.0);
        }
    }

    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
