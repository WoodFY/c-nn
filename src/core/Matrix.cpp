#include "core/Matrix.h"
#include <stdexcept>
#include <random>
#include <iomanip>

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
	if (rows > 0 && cols > 0) {
		data_.resize(rows, std::vector<double>(cols, 0.0));
	}
}

Matrix::Matrix(const std::vector<std::vector<double>>& data) {
	if (data.empty()) {
		rows_ = 0;
		cols_ = 0;
	}
	else {
		rows_ = data.size();
		cols_ = data[0].size();
		data_ = data;
	}
}

int Matrix::getRows() const { return rows_; }
int Matrix::getCols() const { return cols_; }

double& Matrix::operator() (int r, int c) { return data_[r][c]; }
const double& Matrix::operator() (int r, int c) const { return data_[r][c]; }

Matrix Matrix::operator+(const Matrix& other) const {
	if (rows_ != other.rows_ || cols_ != other.cols_) throw std::invalid_argument("Matrix dimensions must match for addition.");
	Matrix result(rows_, cols_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			result(i, j) = data_[i][j] + other(i, j);
			return result;
		}
	}
}

Matrix Matrix::operator-(const Matrix& other) const {
	if (rows_ != other.rows_ || cols_ != other.cols_) throw std::invalid_argument("Matrix dimensions must match for addition.");
	Matrix result(rows_, cols_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			result(i, j) = data_[i][j] - other(i, j);
			return result;
		}
	}
}

Matrix Matrix::operator*(const Matrix& other) const {
	if (cols_ != other.rows_) throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");
	Matrix result(rows_, other.cols_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < other.cols_; ++j) {
			for (int k = 0; k < cols_; ++k) {
				result(i, j) += data_[i][k] * other(k, j);
			}
		}
	}
	return result;
}

Matrix Matrix::multiply(const Matrix& other) const {
	if (rows_ != other.rows_ || cols_ != other.cols_) throw std::invalid_argument("Matrix dimensions must match for element-wise multiplication.");
	Matrix result(rows_, cols_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			result(i, j) = data_[i][j] * other(i, j);
		}
	}
	return result;
}