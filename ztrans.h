#ifndef ZTRANS_H
#define ZTRANS_H

struct zt{
    std::complex<double>* data;
    unsigned long length;
};
struct polar{
    double mag;
    double phase;
};
struct cart{
    double rl;
    double im;
};
// common procedures:
struct wave zero_pad(wave const& in_file, long int N, int print = 0);

struct polar cart_to_polar(cart const& in_cart);
struct cart polar_to_cart(polar const& in_polar);
double* get_mag(zt const& ft);
double* get_phs(zt const& ft);

struct zt dft(wave const& in_wave, int print = 0);
#endif
