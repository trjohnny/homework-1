//
// Created by Giovanni and Thomas on 26/10/2023.
//

#ifndef HOMEWORK_1_CSRMATRIX_TPP
#define HOMEWORK_1_CSRMATRIX_TPP

#include <stdexcept>
#include <algorithm>
#include <iostream>

template<typename T>
void CSRMatrix<T>::addValue(int row, int col, T value) {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Indices are out of range");
    }

    // If the value is zero, we don't need to store it in a sparse matrix.
    if (value == T()) return;

    // Find the insertion position in the columns and values vectors.
    int insertPos = row_idx[row];
    while (insertPos < row_idx[row + 1] && columns[insertPos] < col) {
        ++insertPos;
    }

    // If the element already exists, update its value. Otherwise, insert the new value and column index.
    if (insertPos < row_idx[row + 1] && columns[insertPos] == col) {
        values[insertPos] = value;
    } else {
        values.insert(values.begin() + insertPos, value);
        columns.insert(columns.begin() + insertPos, col);

        // Update the row indices of the subsequent rows.
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

    // Find the range of elements in the specified row.
    auto start = row_idx[row];
    auto end = row_idx[row + 1];

    // Find the column index in the range. If found, erase the value and column index.
    auto it = std::lower_bound(columns.begin() + start, columns.begin() + end, col);
    if (it != columns.begin() + end && *it == col) {
        auto index = std::distance(columns.begin(), it);
        values.erase(values.begin() + index);
        columns.erase(columns.begin() + index);

        // Update the row indices of the subsequent rows.
        for (int i = row + 1; i < row_idx.size(); ++i) {
            row_idx[i]--;
        }
    }
}

template<typename T>
T CSRMatrix<T>::getElement(int row, int col) const {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Index out of bounds");
    }

    // Find the range of elements in the specified row.
    auto start = row_idx[row];
    auto end = row_idx[row + 1];

    // Find the column index in the range. If found, return the corresponding value.
    auto it = std::lower_bound(columns.begin() + start, columns.begin() + end, col);
    if (it != columns.begin() + end && *it == col) {
        auto index = std::distance(columns.begin(), it);
        return values[index];
    }
    // If not found, return a default constructed object.
    return T();
}

template<typename T>
void CSRMatrix<T>::setElement(int row, int col, T value) {
    if (row < 0 || row >= this->numRows || col < 0 || col >= this->numCols) {
        throw std::out_of_range("Index out of bounds");
    }
    auto start = row_idx[row];
    auto end = row_idx[row + 1];
    auto it = std::lower_bound(columns.begin() + start, columns.begin() + end, col);

    // If element is not present and the value is not default, add the new value.
    if (it == columns.begin() + end || *it != col) {
        if(value != T())
            addValue(row, col, value);
    }

    // If the new value is default, remove the element. Otherwise, update the element's value.
    else if(value == T()) {
        this->removeValue(row, col);
    } else {
        values[it - columns.begin()] = value;
    }
}

template<typename T>
std::vector<T> CSRMatrix<T>::operator*(const std::vector<T>& vec) const {
    // Ensure the vector size matches the number of matrix columns.
    if (vec.size() != this->getCols()) {
        throw std::invalid_argument("Vector size must be equal to the number of matrix columns");
    }

    std::vector<T> result(this->getRows(), T());

    // Perform the matrix-vector multiplication.
    for (int row = 0; row < this->getRows(); ++row) {
        for (int idx = row_idx[row]; idx < row_idx[row + 1]; ++idx) {
            result[row] += values[idx] * vec[columns[idx]];
        }
    }

    return result;
}

// Outputs the CSR matrix to an output stream.
template<typename T>
std::ostream& operator<<(std::ostream& os, const CSRMatrix<T>& matrix) {
    // Iterate through the matrix rows and columns to print the matrix.
    for (int i = 0; i < matrix.getRows(); ++i) {
        int valIndex = matrix.row_idx[i];
        for (int j = 0; j < matrix.getCols(); ++j) {
            // Print the value if it exists, otherwise print 0.
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