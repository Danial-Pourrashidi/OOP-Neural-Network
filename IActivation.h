#pragma once
#include "Matrix.h"
#include <cmath>
#include <string>
#include <algorithm>

class IActivation {
public:
    virtual ~IActivation() = default;
    virtual Matrix activate(const Matrix& input) const = 0;
    virtual std::string getName() const = 0;
};

class Sigmoid : public IActivation {
public:
    Matrix activate(const Matrix& input) const override {
        Matrix result(input.getRows(), input.getCols());
        for (int i = 0; i < input.getRows(); ++i) {
            for (int j = 0; j < input.getCols(); ++j) {
                result(i, j) = 1.0 / (1.0 + std::exp(-input(i, j)));
            }
        }
        return result;
    }
    std::string getName() const override { return "Sigmoid"; }
};

class ReLU : public IActivation {
public:
    Matrix activate(const Matrix& input) const override {
        Matrix result(input.getRows(), input.getCols());
        for (int i = 0; i < input.getRows(); ++i) {
            for (int j = 0; j < input.getCols(); ++j) {
                result(i, j) = std::max(0.0, input(i, j));
            }
        }
        return result;
    }
    std::string getName() const override { return "ReLU"; }
};
