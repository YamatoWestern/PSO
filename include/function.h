#ifndef FUNCTION_H
#define FUNCTION_H

#include <map>
#include <string>

/**
 * @brief Calculates the sigmoid function.
 * @param x The input value.
 * @return The result of the sigmoid function.
 */
double sigmoid(double x);

/**
 * @brief Calculates the logarithmic sigmoid function.
 * @param n The input value.
 * @return The result of the logarithmic sigmoid function.
 */
double logsig(double n);

/**
 * @brief Determines the sign of a number.
 * @param x The input value.
 * @return 1 if the number is positive, -1 if it is negative, and 0 if it is zero.
 */
int sign(double x);

/**
 * @brief Finds the minimum value in an array.
 * @param index The index of the minimum value.
 * @param min_val The minimum value.
 * @param fx_size The size of the array.
 * @param fx The input array.
 */
void minimum(int& index, double& min_val, int fx_size, double* fx);

/**
 * @brief Calculates the number of bits required to represent a decimal number in binary.
 * @param input The decimal number.
 * @return The number of bits required.
 */
int decimal_2_binary_size(int input);

/**
 * @brief Converts a binary number to a decimal number.
 * @param bsize The number of bits in the binary number.
 * @param bits A pointer to the array of bits.
 * @return The decimal equivalent of the binary number.
 */
int binary_2_decimal(int bsize, char* bits);

/**
 * @brief Adjusts a value to a new range.
 * @param curr The current value.
 * @param max_curr The maximum possible current value.
 * @param max_n The maximum value of the new range.
 * @return The adjusted value.
 */
int adjust(int curr, int max_curr, int max_n);

/**
 * @brief Reads configuration settings from a file.
 * @param configs A map to store the configuration settings.
 */
void read_configs(std::map<std::string, double>& configs);

#endif
