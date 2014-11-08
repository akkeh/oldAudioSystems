#ifndef ZTRANS_H
#define ZTRANS_H
#include <complex>
struct zt{
    std::complex<double>* data;
    unsigned long length;
};

struct zt dft(wave in_wave, int print = 0);
double* get_mag(zt ft);
double* get_phs(zt ft);
#endif
