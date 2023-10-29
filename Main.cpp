#include "CSRMatrix.h"
#include "CSRMatrix.tpp"

int main() {
    CSRMatrix<double> matrix(3, 3);

    // Test case 2: Get the number of rows and columns
    int numRows = matrix.getRows();
    int numCols = matrix.getColumns();
    std::cout << "Number of rows: " << numRows << ", Number of columns: " << numCols << std::endl;

    // Test case 3: Set and get elements
    matrix(0, 0) = 1.0;
    matrix(1, 1) = 2.0;
    matrix(2, 2) = 3.0;

    std::cout << "Matrix(0, 0) = " << matrix(0, 0) << std::endl;
    std::cout << "Matrix(1, 1) = " << matrix(1, 1) << std::endl;
    std::cout << "Matrix(2, 2) = " << matrix(2, 2) << std::endl;
    std::cout << "Matrix(1, 2) = " << matrix(1, 2) << std::endl;

    // Test case 4: Matrix-vector product
    std::vector<double> vec = {1.0, 2.0, 3.0};
    std::vector<double> result = matrix * vec;

    std::cout << "Matrix-Vector Product: ";
    for (double v : result) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    // Test case 5: Print the matrix
    std::cout << "Matrix Contents:" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << matrix(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Test case 6: Access an out-of-bound element
    try {
        double invalidValue = matrix(5, 5);
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range error: " << e.what() << std::endl;
    }

    // Test case 7: Set an out-of-bound element
    try {
        matrix(5, 5) = 5.5;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range error: " << e.what() << std::endl;
    }

    return 0;
}