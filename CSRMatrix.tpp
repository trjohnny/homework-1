//
// Created by Giovanni and Thomas on 26/10/2023.
//

#ifndef HOMEWORK_1_CSRMATRIX_TPP
#define HOMEWORK_1_CSRMATRIX_TPP

#include <stdexcept>
#include <algorithm>
#include <iostream>

template<typename T>
CSRMatrix<T>::CSRMatrix(int rows, int cols) : SparseMatrix<T>(rows, cols) {
    row_idx.resize(rows + 1, 0);
}

template<typename T>
CSRMatrix<T>::CSRMatrix(const SparseMatrix<T>& matrix) : CSRMatrix<T>(matrix.getRows(), matrix.getCols()) {
    SparseMatrix<T>::copyFrom(matrix);
}

template<typename T>
void CSRMatrix<T>::addValue(int row, int col, T value) {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Indices are out of range");
    }

    if (value == T()) return;

    int insertPos = row_idx[row];
    while (insertPos < row_idx[row + 1] && columns[insertPos] < col) {
        ++insertPos;
    }

    if (insertPos < row_idx[row + 1] && columns[insertPos] == col) {
        values[insertPos] = value;
    } else {
        values.insert(values.begin() + insertPos, value);
        columns.insert(columns.begin() + insertPos, col);

        for (int i = row + 1; i < row_idx.size(); ++i) {
            row_idx[i]++;
        }
    }
}

template<typename T>
void CSRMatrix<T>::removeValue(int row, int col) {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Indices are out of range");
    }

    auto start = row_idx[row];
    auto end = row_idx[row + 1];

    auto it = std::lower_bound(columns.begin() + start, columns.begin() + end, col);
    if (it != columns.begin() + end && *it == col) {
        auto index = std::distance(columns.begin(), it);
        values.erase(values.begin() + index);
        columns.erase(columns.begin() + index);

        for (int i = row + 1; i < row_idx.size(); ++i) {
            row_idx[i]--;
        }
    }
}

template<typename T>
int CSRMatrix<T>::getNonZeros() const {
    return values.size();
}

template<typename T>
T CSRMatrix<T>::getElement(int row, int col) const {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Index out of bounds");
    }

    auto start = row_idx[row];
    auto end = row_idx[row + 1];

    auto it = std::lower_bound(columns.begin() + start, columns.begin() + end, col);
    if (it != columns.begin() + end && *it == col) {
        auto index = std::distance(columns.begin(), it);
        return values[index];
    }
    return T();
}

template<typename T>
void CSRMatrix<T>::setElement(int row, int col, T value) {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Index out of bounds");
    }
    auto start = row_idx[row];
    auto end = row_idx[row + 1];
    auto it = lower_bound(columns.begin() + start, columns.begin() + end, col);

    if (it == columns.begin() + end || *it != col) {
        addValue(row, col, value);
        return;
    }

    values[it - columns.begin()] = value;
}

template<typename T>
std::vector<T> CSRMatrix<T>::operator*(const std::vector<T>& vec) const {
    if (vec.size() != this->getCols()) {
        throw std::invalid_argument("Vector size must be equal to the number of matrix columns");
    }

    std::vector<T> result(this->getRows(), T());

    for (int row = 0; row < this->getRows(); ++row) {
        for (int idx = row_idx[row]; idx < row_idx[row + 1]; ++idx) {
            result[row] += values[idx] * vec[columns[idx]];
        }
    }

    return result;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const CSRMatrix<T>& matrix) {
    for (int i = 0; i < matrix.getRows(); ++i) {
        int valIndex = matrix.row_idx[i];
        for (int j = 0; j < matrix.getCols(); ++j) {
            if (valIndex < matrix.row_idx[i + 1] && j == matrix.columns[valIndex]) {
                os << matrix.values[valIndex] << " ";
                ++valIndex;
            } else {
                os << "0 ";
            }
        }
        os << std::endl;
    }
    return os;
}

#endif //HOMEWORK_1_CSRMATRIX_TPP