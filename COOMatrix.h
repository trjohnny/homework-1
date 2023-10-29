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

public:
    COOMatrix(int rows, int cols);

    int getNonZeros() const override;
    T getElement(int row, int col) const override;
    void setElement(int row, int col, const T& value) override;
    std::vector<T> operator*(const std::vector<T>& vec) const override;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const COOMatrix<U>& matrix);

    void addValue(int row, int col, T value);
};

#include "COOMatrix.tpp"

#endif //COO_MATRIX_H