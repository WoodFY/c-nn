#ifndef C_NN_ACTIVATION_H
#define C_NN_ACTIVATION_H

#include <cmath>
#include <functional>
#include <string>

using ActivationFunction = std::function<double(double)>;

struct Sigmoid {
	static double forward(double x);
	static double backward(double activated_x);
};

struct ReLU {
	static double forward(double x);
	static double backward(double activated_x);
};

void get_activation_functions(const std::string& type, ActivationFunction& fwd, ActivationFunction& bwd);

#endif // C_NN_ACTIVATION_H