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
void CSRMatrix<T>::addValue(int row, int col, T value) {
    if (row < 0 || row >= this->rows || col < 0 || col >= this->cols) {
        throw std::out_of_range("Indices are out of range");
    }

    if (value == static_cast<T>(0)) return;  // Ignore zero values

    // Find the position in row_idx where the new value's column index should be inserted
    int insertPos = row_idx[row];
    while (insertPos < row_idx[row + 1] && columns[insertPos] < col) {
        ++insertPos;
    }

    // Check if the value already exists at the (row, col) position
    if (insertPos < row_idx[row + 1] && columns[insertPos] == col) {
        values[insertPos] = value;
    } else {
        // Insert the new value
        values.insert(values.begin() + insertPos, value);
        columns.insert(columns.begin() + insertPos, col);

        // Update row_idx and all subsequent rows
        for (int i = row + 1; i < row_idx.size(); ++i) {
            row_idx[i]++;
        }
    }
}

template<typename T>
int CSRMatrix<T>::getNonZeros() const {
    return values.size();
}

template<typename T>
T CSRMatrix<T>::operator()(int row, int col) const {
    if (row < 0 || row >= this->rows || col < 0 || col >= this->cols) {
        throw std::out_of_range("Index out of bounds");
    }

    auto start = row_idx[row];
    auto end = row_idx[row + 1];

    auto it = std::lower_bound(columns.begin() + start, columns.begin() + end, col);
    if (it != columns.end() && *it == col) {
        auto index = std::distance(columns.begin(), it);
        return values[index];
    }
    return T();  // Return a default constructed object of type T
}

template<typename T>
T& CSRMatrix<T>::operator()(int row, int col) {
    assert(row >= 0 && row < this->rows && col >= 0 && col < this->cols);
    auto start = row_idx[row];
    auto end = row_idx[row + 1];
    auto it = lower_bound(columns.begin() + start, columns.begin() + end, col);

    if (it == columns.begin() + end || *it != col) {
        addValue(row, col, 0);
        it++;
    }

    return values[start + (it - columns.begin())];
}

template<typename T>
std::vector<T> CSRMatrix<T>::operator*(const std::vector<T>& vec) const {
    if (vec.size() != this->getColumns()) {
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
        for (int j = 0; j < matrix.getColumns(); ++j) {
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

template std::ostream& operator<<(std::ostream& os, const CSRMatrix<double>& matrix);

#endif //HOMEWORK_1_CSRMATRIX_TPP