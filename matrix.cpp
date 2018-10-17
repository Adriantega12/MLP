#include "matrix.h"

// Renglones = m, columnas = n
Matrix::Matrix(unsigned int m, unsigned int n) : rows(m), columns(n) {

    for (unsigned int i = 0; i < rows; ++i) {
        matrixContainer.push_back(std::vector<double>(n, 0));
        for (unsigned int j = 0; j < columns; ++j) {
            matrixContainer[i][j] = 0.0;
            }
        }
    }

Matrix::Matrix(std::vector<double> vect)
    : Matrix(1, vect.size()) {
    for (unsigned int i = 0; i < columns; ++i) {
        matrixContainer[0][i] = vect[i];
        }
    }

int Matrix::getRows() {
    return rows;
}

int Matrix::getColumns() {
    return columns;
    }

Matrix Matrix::transpose() {
    Matrix transpose(columns, rows);

    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < columns; ++j) {
            transpose[j][i] = matrixContainer[i][j];
            }
        }

    return transpose;
}

Matrix Matrix::cutFirstRow() {
    Matrix result(rows - 1, columns);

    for (int i = 1; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result[i - 1][j] = matrixContainer[i][j];
            }
        }

    return result;
    }

std::vector<double>& Matrix::operator[](int index) {
    return matrixContainer[index];
    }

Matrix Matrix::operator+(Matrix& m) {
    Matrix result(rows, columns);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            double a = matrixContainer[i][j];
            double b = m.matrixContainer[i][j];
            //result[i][j] = matrixContainer[i][j] + m.matrixContainer[i][j];
            result[i][j] = a + b;
            }
        }

    return result;
    }

Matrix Matrix::operator-(Matrix& m) {
    Matrix result(rows, columns);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            double a = matrixContainer[i][j];
            double b = m.matrixContainer[i][j];
            //result[i][j] = matrixContainer[i][j] + m.matrixContainer[i][j];
            result[i][j] = a - b;
            }
        }

    return result;
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
                sum += matrixContainer[i][k] * m.matrixContainer[k][j];
                }
            mResult.matrixContainer[i][j] = sum;
            }
        }

    return mResult;
}

Matrix Matrix::operator*(double scalar) {
    Matrix result(rows, columns);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result[i][j] = scalar * matrixContainer[i][j];
            }
        }

    return result;
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
            linealCombination += this->matrixContainer[rows][cols] * v[cols];
            }
        vResult[rows] = linealCombination;
        }

    return vResult;
    }

Matrix& Matrix::operator=(Matrix m) {
    matrixContainer.resize(m.rows);

    for (int i = 0; i < m.rows; ++i) {
        matrixContainer[i].resize(m.columns);
        for (int j = 0; j < m.columns; ++j) {
            this->matrixContainer[i][j] = m.matrixContainer[i][j];
            }
        }

    rows = m.rows;
    columns = m.columns;

    return *this;
    }
