#ifndef C_NN_DENSE_LAYER_H
#define C_NN_DENSE_LAYER_H

#include "core/Matrix.h"
#include "core/Activation.h"

class DenseLayer {
public:
	DenseLayer(int input_size, int output_size, ActivationFunction activation, ActivationFunction activation_derivative);
	
	Matrix forward(const Matrix& input_data);
	Matrix backward(const Matrix& output_gradient);

	// Expose member variables for optimizer access
	Matrix weights;
	Matrix biases;
	Matrix weight_gradients;
	Matrix bias_gradients;

private:
	ActivationFunction activation_;
	ActivationFunction activation_derivative_;

	// Cache for backward pass
	Matrix last_input_;
	Matrix last_z_;
};

#endif // C_NN_DENSE_LAYER_H