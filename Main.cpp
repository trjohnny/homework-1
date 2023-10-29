#include "CSRMatrix.h"
#include "CSRMatrix.tpp"
#include "COOMatrix.h"
#include "COOMatrix.tpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <typeinfo>

void runTests(SparseMatrix<double>& matrix) {

    // Test 1: Set and get elements
    matrix(0, 0) = 1.0;
    matrix(1, 1) = 2.0;
    matrix(1, 2) = 3.0;
    matrix(2, 1) = 1.3;
    matrix(1, 0) = 0.5;

    assert(matrix(0, 0) == 1.0 && "Set/Get element failed");
    assert(matrix(1, 1) == 2.0 && "Set/Get element failed");
    assert(matrix(1, 2) == 3.0 && "Set/Get element failed");
    assert(matrix(0, 2) == 0.0 && "Set/Get element failed");

    std::cout << " Test 1: Set and get elements. PASSED!" << std::endl;

    // Test 2: Matrix-vector product
    std::vector<double> vec = {1.0, 2.0, 3.0};
    std::vector<double> result = matrix * vec;

    assert(result[0] == 1);
    assert(result[1] == 13.5);
    assert(result[2] == 2.6);

    std::cout << " Test 2: Matrix-vector product. PASSED!" << std::endl;

    // Test 3: Conversion from CSR to COO and back (only if MatrixType is CSRMatrix)
    if (typeid(matrix) == typeid(CSRMatrix<double>)) {
        COOMatrix<double> coo_from_csr(matrix);
        CSRMatrix<double> csr_from_coo(coo_from_csr);

        assert(coo_from_csr(0, 0) == matrix(0, 0) && "Conversion from CSR to COO failed at (0,0)");
        assert(csr_from_coo(0, 0) == matrix(0, 0) && "Conversion from COO to CSR failed at (0,0)");
        std::cout << " Test 3: Conversion between CSR and COO. PASSED!" << std::endl;
    }
}

int main() {
    std::cout << "Testing CSRMatrix" << std::endl;
    CSRMatrix<double> csr(3, 3);
    runTests(csr);

    return 0;
}
