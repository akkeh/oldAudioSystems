#include <cmath>
#include <complex>
#include <fstream>
#include "audioproc.h"
#include "ztrans.h"

zt dft(wave in_file, int print) {
    zt dft_out;
    unsigned long length = in_file.length;
    dft_out.data = new std::complex<double>[length];
    dft_out.length = length;
    
    std::complex<double> csin;
    std::complex<double> z;
    std::complex<double> bin;
    if(print==1) printf("length: %li\n", length);
    for(long int k=0; k<length; k++) {
        if(print==1) printf("done: %li;\tto go: %li\n", k, length-k);
        bin = 0 + 0i;
        for(long int n=0; n<length; n++) {
            z = -1i * 2*M_PI * k * n / length;
            csin = std::exp(z);
            bin+=in_file.data[n]*csin;
        }
        dft_out.data[k] = bin;
    }
    return dft_out;
}
