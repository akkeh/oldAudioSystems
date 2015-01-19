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

    // init output buffer
    sig X;
    X.re = new double[N];
    X.im = new double[N];
    X.N = N;
    for(unsigned long int k=0; k<N; k++) {
        X.re[k] = 0;
        X.im[k] = 0;
    }
    
    // rearrange input buffer
    sig buf;
    buf.re = new double[N];
    buf.im = new double[N];
    arrange(x, &buf, 0);

    // allocate temp. output buffers:
    sig* tX = new mdsig;
    (*(mdsig*)tX).data = new sig[maxd];
    for(unsigned int d=0; d<maxd; d++) {
        (*(mdsig*)tX).data[d].re = new double[N];
        (*(mdsig*)tX).data[d].im = new double[N];
        (*(mdsig*)tX).data[d].N = N;
    }
    (*(mdsig*)tX).N = maxd;
    
    //  perform fft:
    int tXcount[maxd];
    for(unsigned long int d=0; d<maxd; d++) tXcount[d] = 0;
    unsigned long int filled = 0;
    unsigned long int readp = 0;
    unsigned long int d;
    while(readp < (N)) {
        if((filled > 0) && (tXcount[filled-1] == tXcount[filled-2])) {    // combine last 2 tX buffers:
            std::cout<<"combine\n \tfilled: "<<filled<<std::endl;
            d = (std::log10(N)/std::log10(2))/ (tXcount[filled-2]) - 1;
            for(unsigned long int k=0; k<N; k++) {
            std::cout<<"comb: "<<k<<" "<<d<<"\n";
                (*(mdsig*)tXcount).data[filled-2].re[k] += (*(mdsig*)tXcount).data[filled-1].re[k] * (*(mdsig*)W).data[d].re[k] - (*(mdsig*)tXcount).data[filled-1].im[k] * (*(mdsig*)W).data[d].im[k];
                (*(mdsig*)tXcount).data[filled-2].im[k] += (*(mdsig*)tXcount).data[filled-1].im[k] * (*(mdsig*)W).data[d].re[k] + (*(mdsig*)tXcount).data[filled-1].re[k] * (*(mdsig*)W).data[d].im[k];
            }
            tXcount[filled-2] *= 2;
            tXcount[filled-1] = 0;
            filled--;
        } else {    // fill 2 tX buffers:
            if (filled > 0) std::cout<<"fill\n\tcount: "<<tXcount[filled-2]<<"\t count: "<<tXcount[filled-1]<<std::endl;;
            for(int o=0; o<2; o++) {
                for(unsigned long int k=0; k<N; k++) {
                    (*(mdsig*)tX).data[filled+o].re[k] = x.re[readp+(2*o)];
                    (*(mdsig*)tX).data[filled+o].im[k] = x.im[readp+(2*o)];
                    
                    (*(mdsig*)tX).data[filled+o].re[k] += x.re[readp+1+(2*o)] * (*(mdsig*)W).data[maxd-1].re[k] - x.im[readp+1+(2*o)] * (*(mdsig*)W).data[maxd-1].im[k];
                    (*(mdsig*)tX).data[filled+o].im[k] += x.re[readp+1+(2*o)] * (*(mdsig*)W).data[maxd-1].im[k] + x.im[readp+1+(2*o)] * (*(mdsig*)W).data[maxd-1].re[k]; 
                }
                tXcount[filled+o] = 2;
            }
            filled+=2;
            readp+=4;
        }
    }
    std::cout<<"eind\n";
    
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
