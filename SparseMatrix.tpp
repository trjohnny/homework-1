//
// Created by Giovanni and Thomas on 29/10/2023.
//

#ifndef HOMEWORK_1_SPARSEMATRIX_TPP
#define HOMEWORK_1_SPARSEMATRIX_TPP

#include "SparseMatrix.h"
#include <algorithm>
#include <stdexcept>

template<typename T>
bool SparseMatrix<T>::equals(const SparseMatrix<T>& matrix) const {
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.numCols; ++j) {
            if (matrix.getElement(i, j) != this->getElement(i, j)) return false;
        }
    }
    return true;
}

template<typename T>
void SparseMatrix<T>::copyFrom(const SparseMatrix<T>& mat) {
    for (int i = 0; i < mat.getRows(); ++i) {
        for (int j = 0; j < mat.numCols; ++j) {
            if (mat.getElement(i, j) != T()) {
                addValue(i, j, mat.getElement(i, j));
            }
        }
    }
}


#endif //HOMEWORK_1_SPARSEMATRIX_TPP
