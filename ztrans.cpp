#include <cmath>
#include <complex>
#include <fstream>
#include "audioproc.h"
#include "ztrans.h"

double* get_mag(zt ft) {
    long int length = ft.length;
    double* mX = new double[length];
    double rl, im;
    for(long int k=0; k<length; k++) {
        rl = real(ft.data[k]);
        im = imag(ft.data[k]);
        mX[k] = std::sqrt((rl*rl) + (im*im));
    }
    return mX;
}
