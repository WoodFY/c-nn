#include "layers/DenseLayer.h"
#include <cmath>

DenseLayer::DenseLayer(int input_size, int output_size, ActivationFunction activation, ActivationFunction activation_derivative)
	: activation_(activation), activation_derivative_(activation_derivative) {
	// Xavier/Glorot initialization
	double limit = sqrt(6.0 / (input_size + output_size));
	weights = Matrix::random(output_size, input_size) * limit;
	biases = Matrix(output_size, 1);
}

Matrix DenseLayer::forward(const Matrix& input_data) {
	last_input_ = input_data;
	last_z_ = (weights * last_input_) + biases;
	return Matrix::apply(last_z_, activation_);
}

Matrix DenseLayer::backward(const Matrix& output_gradient) {
	Matrix d_activation = Matrix::apply(last_z_, activation_derivative_);
	Matrix delta = output_gradient.multiply(d_activation);

	weight_gradients = delta * last_input_.transpose();
	bias_gradients = delta;

	return weights.transpose() * delta;
}