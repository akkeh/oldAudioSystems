#include "azath.h"
#include <iostream>

sig fft(sig const& x) {
    unsigned long N = x.N;
    unsigned long testN = 2;
    unsigned int maxd = 0;
    while(testN < N) {                  //  if N !power of 2?
        testN+=testN;
        ++maxd;                         
    }
//    if(testN != N) { x = zeropad(x, testN); N = testN;  //  zeropad
    ++maxd;                             //  get max depth;
    
    //  calculate twiddle factors:    
    sig* W = new mdsig;
    (*(mdsig*)W).data = new sig[maxd];
    for(unsigned int d=0; d<maxd; d++) {
        (*(mdsig*)W).data[d].re = new double[N];
        (*(mdsig*)W).data[d].im = new double[N];
        for(unsigned long k=0; k<N; k++) {
            (*(mdsig*)W).data[d].re[k] = std::cos(TWOPI * (double)k * std::pow(2, d) / (double)N);
            (*(mdsig*)W).data[d].im[k] = -std::sin(TWOPI * (double)k * std::pow(2, d) / (double)N);
        }
        (*(mdsig*)W).data[d].N = N;
    }
    (*(mdsig*)W).N = maxd;

    //  perform fft:
    return fft1d(x, N, 0, W);
}

sig fft1d(sig const& x, unsigned long N, unsigned long d, sig* &W) {
    if(x.N < 2) {
       return dft1d(x, N, d); 
    } else {
        sig xe = decimate(x, 0);
        sig xo = decimate(x, 1);

        return sig_add(fft1d(xe, N, d+1, W), sig_mul(fft1d(xo, N, d+1, W), (*(mdsig*)W).data[d]));
    }
}




sig dft1d(sig const& x, unsigned long N, unsigned long d) {
    
    unsigned long len = x.N;
    sig X;
    X.N = N;
    X.re = new double[N];
    X.im = new double[N];
    
    //  perform DFT:
    for(unsigned long k=0; k<N; k++) {
        X.re[k] = 0; X.im[k] = 0;
        for(unsigned long n=0; n<len; n++) {
            X.re[k] += x.re[n];
            X.im[k] += x.im[n];
        }
    }
    return X;
}
