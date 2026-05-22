#include "Matrix.h"
#include <random>
#include <iomanip>

void Matrix::allocateMemory() {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols](); // initialize to 0
    }
}

void Matrix::freeMemory() {
    if (data) {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    allocateMemory();
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    allocateMemory();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;
    
    // Safe assignment against allocation failure
    double** newData = new double*[other.rows];
    for(int i = 0; i < other.rows; ++i) {
        newData[i] = new double[other.cols];
        for(int j = 0; j < other.cols; ++j) {
            newData[i][j] = other.data[i][j];
        }
    }
    
    freeMemory();
    data = newData;
    rows = other.rows;
    cols = other.cols;
    return *this;
}

Matrix::~Matrix() {
    freeMemory();
}

double& Matrix::operator()(int r, int c) {
    return data[r][c];
}

const double& Matrix::operator()(int r, int c) const {
    return data[r][c];
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw DimensionMismatchException(rows, cols, other.rows, other.cols);
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            double sum = 0;
            for (int k = 0; k < cols; ++k) {
                sum += data[i][k] * other.data[k][j];
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows == other.rows && cols == other.cols) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] + other.data[i][j];
            }
        }
        return result;
    } else if (cols == other.cols && other.rows == 1) { 
        // Broadcasting a row vector (bias)
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] + other.data[0][j];
            }
        }
        return result;
    } else {
        throw DimensionMismatchException(rows, cols, other.rows, other.cols);
    }
}

void Matrix::randomize() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = dis(gen);
        }
    }
}

void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(8) << std::setprecision(4) << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Matrix::save(std::ofstream& out) const {
    out << rows << " " << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            out << data[i][j] << " ";
        }
        out << "\n";
    }
}

void Matrix::load(std::ifstream& in) {
    int r, c;
    in >> r >> c;
    if (r != rows || c != cols) {
        freeMemory();
        rows = r;
        cols = c;
        allocateMemory();
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            in >> data[i][j];
        }
    }
}
