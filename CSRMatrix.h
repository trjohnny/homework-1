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

    void addValue(int row, int col, T value) override;
    void removeValue(int row, int col) override;

public:

    CSRMatrix(int rows, int cols) : SparseMatrix<T>(rows, cols) {
        row_idx.resize(rows + 1, 0);
    }

    CSRMatrix(const SparseMatrix<T>& matrix) : CSRMatrix<T>(matrix.getRows(), matrix.getCols()) {
        SparseMatrix<T>::copyFrom(matrix);
    }

    int getNonZeros() const override {
        return values.size();
    };
    T getElement(int row, int col) const override;
    void setElement(int row, int col, T value) override;
    std::vector<T> operator*(const std::vector<T>& vec) const override;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const CSRMatrix<U>& matrix);
};

#include "CSRMatrix.tpp"

#endif // CSR_MATRIX_H