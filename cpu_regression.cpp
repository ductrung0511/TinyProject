#include "include/Matrix.hpp"
#include "include/Vector.hpp"
#include "include/LinearSystem.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

// Constants
const int NUM_FEATURES = 6;
const int TOTAL_FEATURES = 10;
const double TRAIN_RATIO = 0.8;

// Function to read dataset
void LoadData(const std::string& filename,
              std::vector<std::vector<double>>& features,
              std::vector<double>& targets) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<double> row;

        // Skip first two columns (vendor + model)
        std::getline(ss, token, ',');
        std::getline(ss, token, ',');

        // Read next 6 predictive features
        for (int i = 0; i < NUM_FEATURES; ++i) {
            std::getline(ss, token, ',');
            row.push_back(std::stod(token));
        }

        // Read PRP (9th column)
        std::getline(ss, token, ','); // PRP
        double prp = std::stod(token);

        features.push_back(row);
        targets.push_back(prp);
    }
}

// Function to compute RMSE
double ComputeRMSE(const Vector& predicted, const Vector& actual) {
    double sum = 0.0;
    for (int i = 0; i < predicted.Size(); ++i) {
        double diff = predicted[i] - actual[i];
        sum += diff * diff;
    }
    return std::sqrt(sum / predicted.Size());
}

int main() {
    std::vector<std::vector<double>> all_features;
    std::vector<double> all_targets;

    // Load data
    LoadData("data/machine.data", all_features, all_targets);
    int total_samples = all_features.size();
    int train_samples = static_cast<int>(total_samples * TRAIN_RATIO); // 80% for training
    int test_samples = total_samples - train_samples;
    std::cout << "Total samples: " << total_samples << "\n";   
    std::cout << "Training samples: " << train_samples << "\n"; 

    // Shuffle data
    std::vector<int> indices(total_samples);
    for (int i = 0; i < total_samples; ++i) indices[i] = i;
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(42));

    // Prepare training matrix and vector
    Matrix A_train(train_samples, NUM_FEATURES);
    Vector b_train(train_samples);

    for (int i = 0; i < train_samples; ++i) {
        int idx = indices[i];
        for (int j = 0; j < NUM_FEATURES; ++j) {
            A_train(i + 1, j + 1) = all_features[idx][j];
        }
        b_train[i] = all_targets[idx];
    }

    // Prepare test matrix and vector
    Matrix A_test(test_samples, NUM_FEATURES);
    Vector b_test(test_samples);

    for (int i = 0; i < test_samples; ++i) {
        int idx = indices[train_samples + i];
        for (int j = 0; j < NUM_FEATURES; ++j) {
            A_test(i + 1, j + 1) = all_features[idx][j];
        }
        b_test[i] = all_targets[idx];
    }

    // Construct A^T * A and A^T * b for normal equations
    Matrix At = A_train.Transpose();
    Matrix AtA = At * A_train;
    Vector Atb = At * b_train;

    // Solve system
    LinearSystem system(AtA, Atb);
    Vector weights = system.Solve();

    std::cout << "Weights:\n";
    weights.Print();

    // Predict on test data
    Vector predictions(test_samples);
    for (int i = 0; i < test_samples; ++i) {
        double sum = 0.0;
        for (int j = 0; j < NUM_FEATURES; ++j) {
            sum += A_test(i + 1, j + 1) * weights[j];
        }
        predictions[i] = sum;
    }

    // Compute RMSE
    double rmse = ComputeRMSE(predictions, b_test);

    std::cout << "Linear Regression Weights:\n";
    for (int i = 0; i < NUM_FEATURES; ++i) {
        std::cout << "x" << (i + 1) << " = " << weights[i] << "\n";
    }

    std::cout << "\nTest RMSE = " << rmse << std::endl;

    return 0;
}
