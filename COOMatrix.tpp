//
// Created by Giovanni and Thomas on 29/10/2023.
//

#ifndef HOMEWORK_1_COOMATRIX_TPP
#define HOMEWORK_1_COOMATRIX_TPP


#include <algorithm>
#include <stdexcept>

template<typename T>
COOMatrix<T>::COOMatrix(int numRows, int numCols) : SparseMatrix<T>(numRows, numCols) {}

template<typename T>
COOMatrix<T>::COOMatrix(const SparseMatrix<T>& matrix) : COOMatrix<T>(matrix.getRows(), matrix.getCols()) {
    SparseMatrix<T>::copyFrom(matrix);
}

template<typename T>
int COOMatrix<T>::getNonZeros() const {
    return values.size();
}

template<typename T>
T COOMatrix<T>::getElement(int row, int col) const {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Index out of bounds");
    }

    for (size_t i = 0; i < values.size(); ++i) {
        if (rows[i] == row && cols[i] == col) {
            return values[i];
        }
    }
    return T();
}

template<typename T>
void COOMatrix<T>::setElement(int row, int col, T value) {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Index out of bounds");
    }

    for (size_t i = 0; i < values.size(); ++i) {
        if (rows[i] == row && cols[i] == col) {
            if (value == T()) this->removeValue(row, col);
            else values[i] = value;
            return;
        }
    }
    addValue(row, col, value);
}

template<typename T>
std::vector<T> COOMatrix<T>::operator*(const std::vector<T>& vec) const {
    if (vec.size() != this->getCols()) {
        throw std::invalid_argument("Vector size must match the number of columns in the matrix");
    }
    std::vector<T> result(this->getRows(), T());
    for (size_t i = 0; i < values.size(); ++i) {
        result[rows[i]] += values[i] * vec[cols[i]];
    }
    return result;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const COOMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.values.size(); ++i) {
        os << "(" << matrix.rows[i] << ", " << matrix.cols[i] << ", " << matrix.values[i] << ")\n";
    }
    return os;
}

template<typename T>
void COOMatrix<T>::addValue(int row, int col, T value) {
    if (row < 0 || row >= this->getRows() || col < 0 || col >= this->getCols()) {
        throw std::out_of_range("Row or column index out of range");
    }
    if (value == T()) return;

    values.push_back(value);
    rows.push_back(row);
    cols.push_back(col);
}

template<typename T>
void COOMatrix<T>::removeValue(int row, int col) {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Indices are out of range");
    }

    for (size_t i = 0; i < rows.size(); ++i) {
        if (rows[i] == row && cols[i] == col) {
            rows.erase(rows.begin() + i);
            cols.erase(cols.begin() + i);
            values.erase(values.begin() + i);
            return;
        }
    }
}


#endif //HOMEWORK_1_COOMATRIX_TPP
