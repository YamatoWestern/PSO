#include "function.h"

#include <map>
#include <limits>
#include <string>
#include <math.h>

double sigmoid(double x) {
    double exp_value;
    double return_value;

    /*** Exponential calculation ***/
    exp_value = exp((double) -x);

    /*** Final sigmoid value ***/
    return_value = 1 / (1 + exp_value);

    return return_value;
}

double logsig(double n) {
    return 1 / (1 + exp(-n));
}

int sign(double x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

void minimum(int& index, double& min_val, int fx_size, double* fx) {
    min_val = std::numeric_limits<double>::max();
    index = -1;
    for (int i = 0; i < fx_size; i++) {
        if (fx[i] < min_val) {
            min_val = fx[i];
            index = i;
        }
    }
}

int decimal_2_binary_size(int input) {
    int i = 1;
    while (input > 1) {
        input >>= 1;
        i++;
    }
    return i;
}

int binary_2_decimal(int bsize, char* bits) {
    int j = 1;
    int sum = 0;
    for (int i = 0; i < bsize; i++) {
        sum += (j * bits[i]);
        j <<= 1;
    }
    return sum;
}

int adjust(int curr, int max_curr, int max_n) {
    return (curr * max_n) / max_curr;
}

void read_configs(std::map<std::string, double>& configs){
    FILE* ptr = NULL;
    ptr = fopen("config.txt", "r");
    if(ptr){
        char key[10];
        double val;
        while(fscanf(ptr, "%s %lf\n", key, &val) != EOF){
            configs[key] = val;
        }
        fclose(ptr);
    }
}