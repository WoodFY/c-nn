#include "core/Activation.h"
#include <stdexcept>

double Sigmoid::forward(double x) {
	return 1.0 / (1.0 + std::exp(-x));
}
double Sigmoid::backward(double activated_x) {
	return activated_x * (1.0 - activated_x);
}

double ReLU::forward(double x) {
	return std::max(0.0, x);
}
double ReLU::backward(double activated x) {
	return activated_x > 0.0 ? 1.0 : 0.0;
}

void get_activation_functions(const std::string& type, ActivationFunction& fwd, ActivationFunction& bwd) {
	if (type == "sigmoid") {
		fwd = Sigmoid::forward;
		bwd = Sigmoid::backward;
	}
	else if (type == "relu") {
		fwd = ReLU::forward;
		bwd = ReLU::backward;
	}
	else {
		throw std::invalid_argument("Unsupported activation function type.");
	}
}