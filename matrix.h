#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
    private:
        std::vector<std::vector<double>> matrixContainer;
        unsigned int rows;
        unsigned int columns;

    public:
        Matrix(unsigned int m, unsigned int n);

        int getRows();
        int getColumns();

        std::vector<double>& operator[](int index);
        Matrix* operator*(Matrix& m);
        std::vector<double>* operator*(std::vector<double>& v);
    };

#endif // MATRIX_H
