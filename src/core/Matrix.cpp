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

Matrix Matrix::operator*(double scalar) const {
	Matrix result(rows_, cols_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			result(i, j) = data_[i][j] * scalar;
		}
	}
	return result;
}

Matrix Matrix::operator+(double scalar) const {
	Matrix result(rows_, cols_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			result(i, j) = data_[i][j] + scalar;
		}
	}
	return result;
}

Matrix Matrix::transpose() const {
	Matrix result(cols_, rows_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			result(j, i) = data_[i][j];
		}
	}
	return result;
}

Matrix Matrix::apply(const Matrix& m, const std::function<double(double)>& func) {
	Matrix result = m;
	for (int i = 0; i < result.rows_; ++i) {
		for (int j = 0; j < result.cols_; ++j) {
			result(i, j) = func(result(i, j));
		}
	}
	return result;
}

Matrix Matrix::random(int rows, int cols) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1.0, 1.0);
	Matrix result(rows, cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			result(i, j) = dis(gen);
		}
	}
	return result;
}

void Matrix::print() const {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			std::cout << std::fixed << std::setprecision(4) << data_[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}