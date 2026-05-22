#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Exceptions.h"

class Matrix {
private:
    int rows;
    int cols;
    double** data;

    void allocateMemory();
    void freeMemory();

public:
    Matrix(int r, int c);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    double& operator()(int r, int c);
    const double& operator()(int r, int c) const;

    Matrix operator*(const Matrix& other) const;
    Matrix operator+(const Matrix& other) const;

    void randomize();
    void print() const;
    
    // For persistence bonus
    void save(std::ofstream& out) const;
    void load(std::ifstream& in);
};
