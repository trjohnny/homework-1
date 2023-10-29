// CSRMatrix.h

#ifndef CSR_MATRIX_H
#define CSR_MATRIX_H

#include "SparseMatrix.h"
#include <vector>
#include <iostream>

template<typename T>
class CSRMatrix : public SparseMatrix<T> {
private:
    std::vector<T> values;
    std::vector<int> columns;
    std::vector<int> row_idx;

public:
    CSRMatrix(int rows, int cols);

    int getNonZeros() const override;
    T getElement(int row, int col) const override;
    void setElement(int row, int col, const T& value) override;
    std::vector<T> operator*(const std::vector<T>& vec) const override;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const CSRMatrix<U>& matrix);

    void addValue(int row, int col, T value);
};

#include "CSRMatrix.tpp"

#endif // CSR_MATRIX_H