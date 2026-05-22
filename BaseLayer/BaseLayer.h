#pragma once
#include "Matrix.h"
#include <fstream>

class BaseLayer {
public:
    virtual ~BaseLayer() = default;
    virtual Matrix forward(const Matrix& input) = 0;
    
    // For persistence bonus
    virtual void save(std::ofstream& out) const = 0;
    virtual void load(std::ifstream& in) = 0;
};
