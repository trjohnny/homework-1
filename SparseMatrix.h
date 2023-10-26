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

    SparseMatrix(int rows, int cols) : rows(rows), cols(cols) {}

    int getRows() const {
        return rows;
    }

    int getColumns() const {
        return cols;
    }

    virtual int getNonZeros() const = 0;

    virtual T& operator()(int row, int col) = 0;
    virtual T operator()(int row, int col) const = 0;
    virtual std::vector<double> operator*(const std::vector<double>& vec) const = 0;

    virtual std::string toString() const = 0;

    virtual ~SparseMatrix() = default;

protected:

    const int rows;
    const int cols;

};


#endif //HOMEWORK_1_SPARSEMATRIX_H
