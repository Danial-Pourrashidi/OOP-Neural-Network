#include "NeuralNetwork.h"
#include "DenseLayer.h"
#include "IActivation.h"
#include <iostream>

NeuralNetwork::~NeuralNetwork() {
    for (BaseLayer* layer : layers) {
        delete layer;
    }
}

void NeuralNetwork::addLayer(BaseLayer* layer) {
    layers.push_back(layer);
}

Matrix NeuralNetwork::predict(const Matrix& input) {
    Matrix current = input;
    for (BaseLayer* layer : layers) {
        current = layer->forward(current);
    }
    return current;
}

void NeuralNetwork::saveModel(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << "\n";
        return;
    }
    out << layers.size() << "\n";
    for (BaseLayer* layer : layers) {
        layer->save(out);
    }
    out.close();
}

void NeuralNetwork::loadModel(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << "\n";
        return;
    }
    
    // Free existing layers before loading
    for (BaseLayer* layer : layers) {
        delete layer;
    }
    layers.clear();

    size_t numLayers;
    if (!(in >> numLayers)) return;

    for (size_t i = 0; i < numLayers; ++i) {
        std::string layerType;
        in >> layerType;
        if (layerType == "DenseLayer") {
            std::string actName;
            in >> actName;
            IActivation* act = nullptr;
            if (actName == "Sigmoid") act = new Sigmoid();
            else if (actName == "ReLU") act = new ReLU();
            
            // Create dummy DenseLayer to hold the loaded weights. 
            // The dimensions will be overwritten by Matrix::load()
            DenseLayer* dl = new DenseLayer(1, 1, act);
            dl->load(in);
            layers.push_back(dl);
        }
    }
    in.close();
}
