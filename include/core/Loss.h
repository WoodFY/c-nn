#ifndef C_NN_LOSS_H
#define C_NN_LOSS_H

#include "core/Matrix.h"

struct MeanSquareError {
	static double forward(const Matrix& predictions, const Matrix& targets);
	static Matrix backward(const Matrix& predictions, const Matrix& targets);
};

#define C_NN_LOSS_H