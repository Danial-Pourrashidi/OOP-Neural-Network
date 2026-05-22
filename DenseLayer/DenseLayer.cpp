#include "DenseLayer.h"

DenseLayer::DenseLayer(int inputSize, int outputSize, IActivation* act) 
    : weights(inputSize, outputSize), biases(1, outputSize), activation(act) {
    weights.randomize();
    biases.randomize();
}

DenseLayer::~DenseLayer() {
    delete activation;
}

Matrix DenseLayer::forward(const Matrix& input) {
    // Math syntax bonus: C = A * B + bias
    Matrix z = input * weights + biases;
    
    if (activation) {
        return activation->activate(z);
    }
    return z;
}

void DenseLayer::save(std::ofstream& out) const {
    out << "DenseLayer\n";
    if (activation) out << activation->getName() << "\n";
    else out << "None\n";
    weights.save(out);
    biases.save(out);
}

void DenseLayer::load(std::ifstream& in) {
    // Weights and biases dimensions and data are read directly
    weights.load(in);
    biases.load(in);
}
