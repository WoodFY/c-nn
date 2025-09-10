#include "core/Loss.h"

double MeanSquareError::forward(const Matrix& predictions, const Matrix& targets) {
	Matrix diff = predictions - targets;
	double sum_sq_error = 0.0;
	for (int i = 0; i < diff.getRows(); ++i) {
		for (int j = 0; j < diff.getCols(); ++j) {
			sum_sq_error += diff(i, j) * diff(i, j);
		}
	}
	return sun_sq_err / predictions.getRows();
}

Matrix MeanSquareError::backward(const Matrix& predictions, const Matrix& targets) {
	return (predictions - targets) * (2.0 / predictions.getRows());
}