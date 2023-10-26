//
// Created by Giovanni on 26/10/2023.
//

#ifndef HOMEWORK_1_SPARSEMATRIX_H
#define HOMEWORK_1_SPARSEMATRIX_H


class SparseMatrix {

    static_assert(std::is_arithmetic_v<T>, "SparseMatrix can only be instantiated with arithmetic types");
    const int rows;
    const int coloumns;

public:

    SparseMatrix(int rows, int columns) : rows(rows), columns(columns) {}

    int getRows() const {
        return rows;
    }

    int getColumns() const {
        return columns;
    }

    virtual int getNonZeros() const = 0;

    virtual T& operator()(int row, int col) = 0;
    virtual T operator()(int row, int col) const = 0;
    virtual vector<double> operator*(const vector<double>& vec) const = 0;
    virtual ostream& operator<<(ostream& stream, const SparseMatrix& matrix) = 0;

    virtual ~SparseMatrix() = default;

};


#endif //HOMEWORK_1_SPARSEMATRIX_H
