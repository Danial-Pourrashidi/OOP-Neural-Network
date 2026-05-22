#pragma once
#include <exception>
#include <string>

class DimensionMismatchException : public std::exception {
private:
    std::string message;
public:
    DimensionMismatchException(int r1, int c1, int r2, int c2) {
        message = "Dimension mismatch: (" + std::to_string(r1) + "x" + std::to_string(c1) + 
                  ") and (" + std::to_string(r2) + "x" + std::to_string(c2) + ")";
    }
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};
