#include "CSRMatrix.h"
#include "CSRMatrix.tpp"
#include "COOMatrix.h"
#include "COOMatrix.tpp"

int main() {
    int numRows = 3;
    int numCols = 3;
    CSRMatrix<double> csr_matrix(numRows, numCols);
    COOMatrix<double> coo_matrix(numRows, numCols);

    // Test case 1: Get the number of numRows and columns
    assert(csr_matrix.getRows() == numRows && "csr_matrix.getRows() does not match numRows");
    assert(csr_matrix.getCols() == numCols && "csr_matrix.getCols() does not match numCols");

    assert(coo_matrix.getRows() == numRows && "coo_matrix.getRows() does not match numRows");
    assert(coo_matrix.getCols() == numCols && "coo_matrix.getCols() does not match numCols");

    std::cout << "Test 1: rows and columns. PASSED!" << std::endl;

    // Test case 2: Set and get elements
    csr_matrix(0, 0) = 1.0;
    csr_matrix(1, 1) = 2.0;
    csr_matrix(1, 2) = 3.0;
    csr_matrix(2, 1) = 1.3;
    csr_matrix(1, 0) = 0.5;

    coo_matrix(0, 0) = 1.0;
    coo_matrix(1, 1) = 2.0;
    coo_matrix(1, 2) = 3.0;
    coo_matrix(2, 1) = 1.3;
    coo_matrix(1, 0) = 0.5;

    assert(csr_matrix(0, 0) == 1.0 && "csr_matrix(0,0) should be 1.0");
    assert(csr_matrix(1, 1) == 2.0 && "csr_matrix(1,1) should be 2.0");
    assert(csr_matrix(1, 2) == 3.0 && "csr_matrix(1,2) should be 3.0");
    assert(csr_matrix(0, 2) == 0.0 && "csr_matrix(0,2) should be 0.0");

    assert(coo_matrix(0, 0) == 1.0 && "coo_matrix(0,0) should be 1.0");
    assert(coo_matrix(1, 1) == 2.0 && "coo_matrix(1,1) should be 2.0");
    assert(coo_matrix(1, 2) == 3.0 && "coo_matrix(1,2) should be 3.0");
    assert(coo_matrix(0, 2) == 0.0 && "coo_matrix(0,2) should be 0.0");

    std::cout << "Test 2: get and set. PASSED!" << std::endl;

    // Test case 3: Matrix-vector product
    std::vector<double> vec = {1.0, 2.0, 3.0};
    std::vector<double> csr_result = csr_matrix * vec;
    std::vector<double> coo_result = coo_matrix * vec;

    assert(csr_result[0] == 1);
    assert(csr_result[1] == 13.5);
    assert(csr_result[2] == 2.6);

    assert(coo_result[0] == 1);
    assert(coo_result[1] == 13.5);
    assert(coo_result[2] == 2.6);

    std::cout << "Test 3: matrix vector product. PASSED!" << std::endl;

    // Test case 4: Access an out-of-bound element

    bool exceptionThrown = false;

    try {
        double invalidValue = csr_matrix(5, 5);
    } catch (const std::out_of_range& e) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
    exceptionThrown = false;

    try {
        double invalidValue = csr_matrix(5, 5);
    } catch (const std::out_of_range& e) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
    exceptionThrown = false;

    try {
        csr_matrix(5, 5) = 5.5;
    } catch (const std::out_of_range& e) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
    exceptionThrown = false;

    try {
        double invalidValue = coo_matrix(5, 5);
    } catch (const std::out_of_range& e) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
    exceptionThrown = false;

    try {
        coo_matrix(5, 5) = 5.5;
    } catch (const std::out_of_range& e) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);

    std::cout << "Test 4: accessing an oob element throws out_of_range exception. PASSED!" << std::endl;

    std::cout << std::endl;
    // Test case 5: Print the csr_matrix
    std::cout << "Matrix Contents:" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << csr_matrix(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}