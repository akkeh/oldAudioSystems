#include "azath.h"
#include <iostream>

/*
    to do:
        - SIMD
        - interger calculation?
*/

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
            if(d==maxd-1) (*(mdsig*)W).data[d].re[k] = 1;
            else (*(mdsig*)W).data[d].re[k] = std::cos(TWOPI * (double)k * std::pow(2, d+1) / (double)N);
            (*(mdsig*)W).data[d].im[k] = -std::sin(TWOPI * (double)k * std::pow(2, d+1) / (double)N);
        }
        (*(mdsig*)W).data[d].N = N;
    }
    (*(mdsig*)W).N = maxd;
    
    // init output buffer
    sig X;
    X.re = new double[N/2];
    X.im = new double[N/2];
    X.N = N/2;
    
    // rearrange input buffer
    sig buf;
    buf.re = new double[N];
    buf.im = new double[N];
    arrange(x, &buf, 0);
    
    // allocate temp. output buffers:
    sig* tX = new mdsig;
    (*(mdsig*)tX).data = new sig[maxd];
    for(unsigned int d=0; d<maxd; d++) {
        (*(mdsig*)tX).data[d].re = new double[N/2];
        (*(mdsig*)tX).data[d].im = new double[N/2];
        (*(mdsig*)tX).data[d].N = N/2;
    }
    (*(mdsig*)tX).N = maxd;
    
    //  perform fft:
    int tXcount[maxd];
    for(unsigned long int d=0; d<maxd; d++) tXcount[d] = 0;
    unsigned long int filled = 0;
    unsigned long int readp = 0;
    unsigned long int dpt;
    double a, b, c, d;
    while((readp < N) || (filled > 1)) {
        if((filled > 1) && (tXcount[filled-2] == tXcount[filled-1])) {    // combine last 2 tX buffers:
            dpt = maxd - std::log10(tXcount[filled-2])/std::log10(2) - 1;
            for(unsigned long int k=0; k<N/2; k++) {
                a = (*(mdsig*)tX).data[filled-1].re[k];
                b = (*(mdsig*)tX).data[filled-1].im[k];
                c = (*(mdsig*)W).data[dpt].re[k];
                d = (*(mdsig*)W).data[dpt].im[k];
                (*(mdsig*)tX).data[filled-2].re[k] += (a * c - b * d);
                (*(mdsig*)tX).data[filled-2].im[k] += (a * d + c * b);
            }
            tXcount[filled-2] *= 2;
            tXcount[filled-1] = 0;
            --filled;
        } else {    // fill 2 tX buffers:
            for(unsigned long int k=0; k<N/2; k++) {
                a = buf.re[readp];
                b = buf.im[readp];
                d = (*(mdsig*)W).data[maxd-1].im[k];

                (*(mdsig*)tX).data[filled].re[k] = a;
                (*(mdsig*)tX).data[filled].im[k] = b;

                a = buf.re[readp+1];
                b = buf.im[readp+1];
                
                (*(mdsig*)tX).data[filled].re[k] += (a - b * d);
                (*(mdsig*)tX).data[filled].im[k] += (a * d + b);
            }
            tXcount[filled] = 2;
            filled++;
            readp+=2;
        }
    }


    for(unsigned long int k=0; k<N/2; k++) {
        X.re[k] = (*(mdsig*)tX).data[0].re[k];
        X.im[k] = (*(mdsig*)tX).data[0].im[k];
    }    
    for(unsigned long int d=0; d<maxd; d++) {
        delete[] (*(mdsig*)tX).data[d].re;
        delete[] (*(mdsig*)tX).data[d].im;
    }
    return X;
}
/*
sig fft1d(sig const& x, unsigned long N, sig* X, unsigned long d, sig* &W, short** odd, unsigned long int id) {
    if(x.N < 2) {
       return dft1d(x, N, d); 
    } else {
        sig xe = decimate(x, 0);        //  only pass pointer + depth to get samples?
        sig xo = decimate(x, 1);

        fft1d(xe, N, d+1, W, odd, id);   //  even
        fft1d(xo, N, d+1, W, odd, id);   //  odd
    }
}




sig dft1d(sig const& x, unsigned long N, unsigned long d) {
    
    unsigned long len = x.N;
    sig X;
    X.N = N;
    X.re = new double[N];       //  verplaats allocatie naar fft()
    X.im = new double[N];
    
    //  perform DFT:
    for(unsigned long k=0; k<N; k++) {
        X.re[k] = 0;
        X.im[k] = 0;
        for(unsigned long n=0; n<len; n++) {
            X.re[k] += x.re[n];
            X.im[k] += x.im[n];
        }
    }
    return X;

}
*/
