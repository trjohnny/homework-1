// COOMatrix.h

#ifndef COO_MATRIX_H
#define COO_MATRIX_H

#include "SparseMatrix.h"
#include <vector>
#include <iostream>

template<typename T>
class COOMatrix : public SparseMatrix<T> {
private:
    std::vector<T> values;
    std::vector<int> rows;
    std::vector<int> cols;

    void addValue(int row, int col, T value) override;
    void removeValue(int row, int col) override;

public:
    COOMatrix(int rows, int cols) : SparseMatrix<T>(rows, cols) {}
    COOMatrix(const SparseMatrix<T>& matrix) : COOMatrix<T>(matrix.getRows(), matrix.getCols()) {
        SparseMatrix<T>::copyFrom(matrix);
    }
    int getNonZeros() const {
        return values.size();
    }

    T getElement(int row, int col) const override;
    void setElement(int row, int col, T value) override;
    std::vector<T> operator*(const std::vector<T>& vec) const override;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const COOMatrix<U>& matrix);
};

#include "COOMatrix.tpp"

#endif //COO_MATRIX_H