#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
    private:
        std::vector<std::vector<double>> matrixContainer;
        unsigned int rows;
        unsigned int columns;

    public:
        Matrix(unsigned int m = 0, unsigned int n = 0);
        Matrix(std::vector<double>);

        int getRows();
        int getColumns();
        Matrix transpose();

        std::vector<double>& operator[](int index);
        Matrix operator*(Matrix& m);
        std::vector<double> operator*(std::vector<double>& v);
        Matrix& operator=(Matrix);
    };

#endif // MATRIX_H
