#include "matrix.h"

// Renglones = m, columnas = n
Matrix::Matrix(unsigned int m, unsigned int n) : rows(m), columns(n) {
    for (unsigned int i = 0; i < m; ++i) {
        matrixContainer.push_back(std::vector<double>(n, 0));
        for (unsigned int j = 0; j < n; ++j) {
            matrixContainer[i][j] = 0.0;
            }
    }
}

int Matrix::getRows() {
    return rows;
}

int Matrix::getColumns() {
    return columns;
    }

std::vector<double>& Matrix::operator[](int index) {
    return matrixContainer[index];
    }

Matrix Matrix::operator*(Matrix& m) {
    double sum;

    // a.rows x a.columns b.rows x b.columns
    if (this->columns != m.rows) {
        // throw MatrixException("A matrix columns and B matrix rows doesn't match.");
        }
    Matrix mResult(this->rows, m.columns);

    // Mult algorithm
    for (unsigned int i = 0; i < this->rows; ++i) {
        for (unsigned int j = 0; j < m.columns; ++j) {
            sum = 0.0;
            for (unsigned int k = 0; k < this->columns; ++k) {
                sum += (*this)[i][k] * m[k][j];
                }
            mResult[i][j] = sum;
            }
        }

    return mResult;
    }

std::vector<double> Matrix::operator*(std::vector<double>& v) {
    if (this->columns != v.size()) {
        // throw MatrixException("M matrix columns doesn't match vector size.");
        }

    std::vector<double> vResult( this->rows, 0 );
    double linealCombination;

    for (unsigned int rows = 0; rows < this->rows; ++rows) {
        linealCombination = 0.0;
        for (unsigned int cols = 0; cols < this->columns; ++cols) {
            linealCombination += (*this)[rows][cols] * v[cols];
            }
        vResult[rows] = linealCombination;
        }

    return vResult;
    }

Matrix& Matrix::operator=(Matrix m) {
    for (int i = 0; i < m.rows; ++i) {
        this->matrixContainer.push_back( std::vector<double>(m.columns, 0) );
        for (int j = 0; j < m.columns; ++j) {
            this->matrixContainer[i][j] = m[i][j];
            }
        }
    }
