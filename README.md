# Sparse Matrix Library

This library provides an efficient representation and manipulation of sparse matrices. Sparse matrices are matrices in which most of the elements are zero. Instead of storing all the values, including the zeros, this library only stores the non-zero values along with their indices, which can lead to significant space savings for large sparse matrices.

## Features

- Support for two types of sparse matrix representations:
  - Compressed Sparse Row (CSR)
  - Coordinate List (COO)
- Templated classes, allowing the use of different numeric types.
- Arithmetic operations and matrix-vector multiplications.
- Efficient memory usage for large sparse matrices.
- Easy conversion between different sparse matrix formats.

## Installation

To use this library in your project, clone this repository and include the necessary header files in your project.

```
git clone https://github.com/trjohnny/sparse-matrix.git
```

## Usage
### Creating a Sparse Matrix

You can create a sparse matrix by specifying its dimensions (rows and columns).

```
CSRMatrix<double> csrMatrix(5, 5);
COOMatrix<double> cooMatrix(5, 5);
```

### Setting Elements

Use the () operator to set the value of a specific element in the matrix.

```
csrMatrix(0, 1) = 2.5;
cooMatrix(2, 4) = 1.5;
```

### Getting Elements
Retrieve the value of a specific element using the () operator.

```
double value1 = csrMatrix(0, 1);
double value2 = cooMatrix(2, 4);
```

### Matrix-Vector Multiplication

Multiply the sparse matrix with a vector using the * operator.

```
std::vector<double> vec = {1.0, 2.0, 3.0, 4.0, 5.0};
std::vector<double> result = csrMatrix * vec;
```

### Converting Between Formats
You can convert between CSR and COO formats using their respective constructors.

```
COOMatrix<double> convertedCOO(csrMatrix);
CSRMatrix<double> convertedCSR(cooMatrix);
```

## Testing
This library includes a set of tests to ensure its correctness. Run the tests by executing the corresponding test suite.

## Contributors

Giovanni Coronica

Thomas Rossi Mel ---> https://github.com/rossimelthomas
