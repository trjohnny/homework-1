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

    // This line checks if T is an arithmetic type (int, float, double...)
    static_assert(std::is_arithmetic_v<T>, "SparseMatrix can only be instantiated with arithmetic types");

public:

    // The proxy class wraps the elements in the matrix so that SparseMatrix(x,y) = element (setter)
    // and SparseMatrix(x,y) (getter) can behave differently
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
    virtual void setElement(int row, int col, T value) = 0;
    bool equals(const SparseMatrix<T>& matrix) const;

    // When SparseMatrix(row, col) is called, a Proxy element is returned
    // but the getter and setter operations are implemented in the Proxy class
    ProxyElement operator()(int row, int col) {
        return ProxyElement(*this, row, col);
    }

    virtual std::vector<T> operator*(const std::vector<T>& vec) const = 0;

protected:

    const int numRows;
    const int numCols;

    // addValue physically inserts an element when it's not available in the SparseMatrix.
    // This is a helper function which is not available to the user who can just modify pre-existing elements.
    virtual void addValue(int row, int col, T value) = 0;
    virtual void removeValue(int row, int col) = 0;

    void copyFrom(const SparseMatrix<T>& mat);

};


#endif //HOMEWORK_1_SPARSEMATRIX_H
