//
// Created by Giovanni and Thomas on 26/10/2023.
//

#ifndef HOMEWORK_1_SPARSEMATRIX_H
#define HOMEWORK_1_SPARSEMATRIX_H

#include <iostream>
#include <vector>
#include <cassert>
#include <numbers>

template<typename T>
class SparseMatrix {

    static_assert(std::is_arithmetic_v<T>, "SparseMatrix can only be instantiated with arithmetic types");

public:

    class ProxyElement {
    public:
        ProxyElement(SparseMatrix& matrix, int row, int col) : matrix(matrix), row(row), col(col) {}

        ProxyElement& operator=(const T& value) {
            matrix.setElement(row, col, value);
            return *this;
        }

        operator T() const {
            return matrix.getElement(row, col);
        }

    private:
        SparseMatrix& matrix;
        int row, col;
    };


    SparseMatrix(int rows, int cols) : numRows(rows), numCols(cols) {}

    int getRows() const {
        return numRows;
    }

    int getCols() const {
        return numCols;
    }

    virtual int getNonZeros() const = 0;

    virtual T getElement(int row, int col) const = 0;
    virtual void setElement(int row, int col, const T& value) = 0;
    ProxyElement operator()(int row, int col) {
        return ProxyElement(*this, row, col);
    }

    virtual std::vector<T> operator*(const std::vector<T>& vec) const = 0;

    virtual ~SparseMatrix() = default;

protected:

    const int numRows;
    const int numCols;

};


#endif //HOMEWORK_1_SPARSEMATRIX_H
