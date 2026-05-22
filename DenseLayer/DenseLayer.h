#pragma once
#include "BaseLayer.h"
#include "IActivation.h"

class DenseLayer : public BaseLayer {
private:
    Matrix weights;
    Matrix biases;
    IActivation* activation;

public:
    DenseLayer(int inputSize, int outputSize, IActivation* act);
    ~DenseLayer();

    Matrix forward(const Matrix& input) override;

    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
};
