#include <iostream>
#include "Matrix.h"
#include "IActivation.h"
#include "DenseLayer.h"
#include "NeuralNetwork.h"
#include "Exceptions.h"
#include "CSVReader.h"
#include <vector>

void testXOR() {
    std::cout << "--- Testing XOR Problem ---\n";
    NeuralNetwork nn;
    // XOR needs a non-linear activation in hidden layer
    nn.addLayer(new DenseLayer(2, 4, new ReLU()));
    nn.addLayer(new DenseLayer(4, 1, new Sigmoid()));

    Matrix X(4, 2);
    X(0, 0) = 0; X(0, 1) = 0;
    X(1, 0) = 0; X(1, 1) = 1;
    X(2, 0) = 1; X(2, 1) = 0;
    X(3, 0) = 1; X(3, 1) = 1;

    std::cout << "Input (XOR):\n";
    X.print();
    
    std::cout << "Forward pass output (untrained):\n";
    Matrix Y = nn.predict(X);
    Y.print();

    nn.saveModel("xor_model.txt");
    std::cout << "Model saved to xor_model.txt\n";

    NeuralNetwork nn2;
    nn2.loadModel("xor_model.txt");
    std::cout << "Model loaded from xor_model.txt\n";
    std::cout << "Forward pass output from loaded model:\n";
    Matrix Y2 = nn2.predict(X);
    Y2.print();
}

void testException() {
    std::cout << "\n--- Testing Exception Handling ---\n";
    try {
        Matrix A(2, 3);
        Matrix B(4, 2); // Incompatible for A * B
        Matrix C = A * B;
    } catch (const DimensionMismatchException& e) {
        std::cerr << "Caught expected exception: " << e.what() << "\n";
    }
}

void testIris() {
    std::cout << "\n--- Testing Iris Dataset (Bonus) ---\n";
    Matrix X(1, 1), Y(1, 1);
    if (CSVReader::loadIrisData("iris.csv", X, Y)) {
        std::cout << "Iris data loaded! " << X.getRows() << " samples.\n";
        NeuralNetwork nn;
        nn.addLayer(new DenseLayer(4, 8, new ReLU()));
        nn.addLayer(new DenseLayer(8, 3, new Sigmoid())); // 3 classes

        // Predict first 5 samples
        Matrix first5(5, 4);
        for(int i=0; i<5; ++i) 
            for(int j=0; j<4; ++j) 
                first5(i, j) = X(i, j);
        
        std::cout << "Prediction for first 5 samples (untrained):\n";
        Matrix preds = nn.predict(first5);
        preds.print();
    } else {
        std::cout << "Could not load iris.csv\n";
    }
}

int main() {
    testXOR();
    testException();
    testIris();
    system("pause");
    return 0;
}
