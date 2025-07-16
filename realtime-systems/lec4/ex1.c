/*
 * Lecture 4 exercise (2), 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

////// Provided code for the lecture
typedef struct myfloat {
    signed char mantissa;
    signed char exponent;
} myfloat_type;

void doub2myfloat(double arg, myfloat_type *res) {
    int exponent;
    double temp;
    exponent = ceil(log(abs(arg)) / log(2)); //base 2 logarithm
    temp = arg * pow(2, 7 - exponent);
    res->mantissa = (signed char)temp;
    res->exponent = exponent - 7;
}

double myfloat2double(myfloat_type *arg1) {
    double res = (double)(arg1->mantissa) * pow(2, arg1->exponent);
    return res;
}

////// My code
int main() {
    double da[100];
    myfloat_type mf[100];
    double decoded[100];

    srand(time(NULL));
    for (int i = 0; i < 100; ++i) {
        da[i] = 1.0 + ((double)rand() / RAND_MAX);
        doub2myfloat(da[i], &mf[i]);
        decoded[i] = myfloat2double(&mf[i]);
    }

    double max_err = 0.0, avg_err = 0.0;
    for (int i = 0; i < 100; ++i) {
        double err = fabs(decoded[i] - da[i]);
        avg_err += err;
        if (err > max_err) max_err = err;
    }
    avg_err /= 100.0;

    printf("Average absolute error: %f\n", avg_err);
    printf("Max absolute error: %f\n", max_err);

    return 0;
}
