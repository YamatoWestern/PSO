#include <iostream>
#include <cassert>
#include <cmath>
#include <limits>
#include <map>
#include <string>

#include "function.h"
#include "model.h"

// Simple assert macro
#define ASSERT(condition) \
    if (!(condition)) { \
        std::cerr << "Assertion failed: " #condition << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        exit(1); \
    }

void test_sigmoid() {
    std::cout << "Testing sigmoid..." << std::endl;
    ASSERT(std::abs(sigmoid(0) - 0.5) < 1e-6);
    ASSERT(std::abs(sigmoid(1) - 0.73105857863) < 1e-6);
    ASSERT(std::abs(sigmoid(-1) - 0.26894142137) < 1e-6);
}

void test_logsig() {
    std::cout << "Testing logsig..." << std::endl;
    ASSERT(std::abs(logsig(0) - 0.5) < 1e-6);
    ASSERT(std::abs(logsig(1) - 0.73105857863) < 1e-6);
    ASSERT(std::abs(logsig(-1) - 0.26894142137) < 1e-6);
}

void test_sign() {
    std::cout << "Testing sign..." << std::endl;
    ASSERT(sign(10) == 1);
    ASSERT(sign(-10) == -1);
    ASSERT(sign(0) == 0);
}

void test_minimum() {
    std::cout << "Testing minimum..." << std::endl;
    double fx[] = {1.0, 2.0, 0.5, 3.0};
    int index;
    double min_val;
    minimum(index, min_val, 4, fx);
    ASSERT(index == 2);
    ASSERT(std::abs(min_val - 0.5) < 1e-6);
}

void test_decimal_2_binary_size() {
    std::cout << "Testing decimal_2_binary_size..." << std::endl;
    ASSERT(decimal_2_binary_size(10) == 4);
    ASSERT(decimal_2_binary_size(1) == 1);
    ASSERT(decimal_2_binary_size(0) == 1);
}

void test_binary_2_decimal() {
    std::cout << "Testing binary_2_decimal..." << std::endl;
    char bits[] = {1, 0, 1, 0};
    ASSERT(binary_2_decimal(4, bits) == 5);
    char bits2[] = {1, 1, 1, 1};
    ASSERT(binary_2_decimal(4, bits2) == 15);
}

void test_adjust() {
    std::cout << "Testing adjust..." << std::endl;
    ASSERT(adjust(5, 10, 100) == 50);
    ASSERT(adjust(0, 10, 100) == 0);
    ASSERT(adjust(10, 10, 100) == 100);
}

void test_model() {
    std::cout << "Testing Model..." << std::endl;
    Model m;
    Model* m2 = m.clone();
    ASSERT(m2 != nullptr);
    delete m2;
    // a simple check to see that the function runs
    char x[] = {1,1,1};
    ASSERT(m.fx_function_solve(3, x, false) == 0);
}

int main() {
    test_sigmoid();
    test_logsig();
    test_sign();
    test_minimum();
    test_decimal_2_binary_size();
    test_binary_2_decimal();
    test_adjust();
    test_model();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
