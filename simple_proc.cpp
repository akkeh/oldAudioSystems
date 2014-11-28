#include <cmath>
#include <cstddef>
#include "simpleproc.h"

double d_abs(double a) {
    return std::sqrt(a*a);
}

double c_abs(double a, double b) {
    return std::sqrt((a*a)+(b*b));
}

double* decimate(double const* arr, unsigned long int N) {
    double* out = NULL; 
    if(((double)N/2.0) == (int)((double)N/2.0)) {
        out = new double[N/2];
        for(unsigned long int n=0; n<N/2; n++) {
            out[n] = arr[n*2];
        }
    }
    return out;
}
