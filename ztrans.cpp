#include <cmath>
#include <complex>
#include <fstream>
#include "audioproc.h"
#include "ztrans.h"

struct polar cart_to_polar(cart const& in_cart) {
    polar polar_out;
    polar_out.mag = std::sqrt(in_cart.rl*in_cart.rl + in_cart.im*in_cart.im);
    polar_out.phase = std::atan2(in_cart.im, in_cart.rl);     //check juistheid phase?
    return polar_out;    
}
struct cart polar_to_cart(polar const& in_polar) {
    cart cart_out;
    cart_out.im = in_polar.mag * std::sin(in_polar.phase);
    cart_out.rl = in_polar.mag * std::cos(in_polar.phase);
    return cart_out;   
}
double* get_mag(zt const& ft) {
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

double* get_phase(zt const& ft) {
    long int length = ft.length;
    double* pX = new double[length];
    double rl, im;
    for(long int k=0; k<length; k++) {
        rl = real(ft.data[k]);
        im = imag(ft.data[k]);
        pX[k] = std::atan2(im, rl);
    }
    return pX;
}

wave zero_pad(wave const& in_wave, long int N, int print) {
    long int length = in_wave.length;
    if(N > length) {
        wave out_wave;
        double out_data[N];
        long int i;
        for(i=0; i<length; i++) {
            out_data[i] = in_wave.data[i];
        }
        if(print == 1) printf("wrote %li samples\n", i);
        for(i=i; i<N; i++) {
            out_data[i] = 0.0;
        }
        if(print == 1) printf("padded %li samples; new length: %li\n", N-length, N);
        out_wave.data = out_data;
        out_wave.length = N;
        out_wave.chn_num = in_wave.chn_num;
        out_wave.fs = in_wave.fs;
        return out_wave;
    } else {
        printf("N < length!\n");
        return in_wave;
    }
}
