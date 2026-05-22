#pragma once
#include "Matrix.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class CSVReader {
public:
    static bool loadIrisData(const std::string& filename, Matrix& X, Matrix& Y) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::vector<std::vector<double>> features;
        std::vector<std::vector<double>> labels;

        std::string line;
        // Skip header if needed
        std::getline(file, line); 

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::stringstream ss(line);
            std::string token;
            std::vector<double> rowFeatures;
            
            for (int i = 0; i < 4; ++i) {
                if (std::getline(ss, token, ',')) {
                    try {
                        rowFeatures.push_back(std::stod(token));
                    } catch(...) {
                        rowFeatures.clear();
                        break;
                    }
                }
            }
            if (rowFeatures.empty()) continue;
            
            std::string labelStr;
            if (std::getline(ss, labelStr, ',')) {
                // Remove trailing carriage return if exists
                if (!labelStr.empty() && labelStr.back() == '\r') {
                    labelStr.pop_back();
                }
                
                std::vector<double> rowLabel = {0, 0, 0};
                if (labelStr == "Iris-setosa" || labelStr == "Setosa") rowLabel[0] = 1.0;
                else if (labelStr == "Iris-versicolor" || labelStr == "Versicolor") rowLabel[1] = 1.0;
                else if (labelStr == "Iris-virginica" || labelStr == "Virginica") rowLabel[2] = 1.0;
                
                features.push_back(rowFeatures);
                labels.push_back(rowLabel);
            }
        }

        if (features.empty()) return false;

        Matrix tempX(features.size(), 4);
        Matrix tempY(labels.size(), 3);
        
        for (size_t i = 0; i < features.size(); ++i) {
            for (int j = 0; j < 4; ++j) {
                tempX(i, j) = features[i][j];
            }
            for (int j = 0; j < 3; ++j) {
                tempY(i, j) = labels[i][j];
            }
        }
        
        X = tempX;
        Y = tempY;
        return true;
    }
};
