#ifndef C_NN_MATRIX_H
#define C_NN_MATRIX_H

#include <vector>
#include <iostream>
#include <functional>

class Matrix {
public:
    Matrix(int rows = 0, int cols = 0);
    Matrix(const std::vector<std::vector<double>>& data);

    int getRows() const;
    int getCols() const;

    double& operator()(int r, int c);
    const double& operator()(int r, int c) const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix multiply(const Matrix& other) const;

    Matrix operator*(double scalar) const;
    Matrix operator+(double scalar) const;

    Matrix transpose() const;
    static Matrix apply(const Matrix& m, const std::function<double(double)>& func);
    static Matrix random(int rows, int cols);
    void print() const;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<double>> data_;
};

#endif // C_NN_MATRIX_H