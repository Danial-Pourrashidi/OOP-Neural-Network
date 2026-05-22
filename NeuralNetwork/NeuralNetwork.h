#pragma once
#include "BaseLayer.h"
#include <vector>
#include <string>

class NeuralNetwork {
private:
    std::vector<BaseLayer*> layers;

public:
    NeuralNetwork() = default;
    ~NeuralNetwork();

    void addLayer(BaseLayer* layer);
    Matrix predict(const Matrix& input);

    void saveModel(const std::string& filename) const;
    void loadModel(const std::string& filename);
};
