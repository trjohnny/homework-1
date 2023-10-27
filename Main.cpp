#include "CSRMatrix.h"
#include "CSRMatrix.tpp"

int main() {
    try {
        CSRMatrix<double> matrix(4, 5);

        // Adding some values
        matrix.addValue(0, 1, 10.5);
        matrix.addValue(1, 3, 5.0);
        matrix.addValue(2, 0, 3.2);
        matrix.addValue(2, 4, 1.0);
        matrix.addValue(3, 2, 8.5);

        // Testing operator()
        std::cout << "Value at (0, 1): " << matrix(0, 1) << std::endl; // Should print 10.5
        std::cout << "Value at (2, 4): " << matrix(2, 4) << std::endl; // Should print 1.0
        std::cout << "Value at (1, 1): " << matrix(1, 1) << std::endl; // Should print 0

        // Testing matrix-vector multiplication
        std::vector<double> vec = {1, 2, 3, 4, 5};
        std::vector<double> result = matrix * vec;
        std::cout << "Matrix-vector product: ";
        for (auto val : result) {
            std::cout << val << " ";
        }
        std::cout << std::endl; // Should print "0 0 3.2 25.5 0 "

        // Testing operator<<
        std::cout << "Matrix representation:" << std::endl;
        std::cout << matrix;
        // Should print something like:
        // 0 10.5 0 0 0
        // 0 0 0 5 0
        // 3.2 0 0 0 1
        // 0 0 8.5 0 0
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}