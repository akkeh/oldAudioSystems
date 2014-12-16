#include "azath.h"
#include <iostream>

sig fft1d(sig const& x, unsigned long N, unsigned long d, sig* &exp) {
    if(x.N < 2) {
       return dft1d(x, N, d, exp); 
    } else {
        sig W;
        W.re = new double[N];
        W.im = new double[N];
        for(unsigned long k=0; k<N; k++) {
            W.re[k] = std::cos(TWOPI * std::pow(2, d)*(double)k /(double)N);
            W.im[k] = -std::sin(TWOPI * std::pow(2, d)*(double)k /(double)N);
        }
        W.N = N;
        sig xe = decimate(x, 0);
        sig xo = decimate(x, 1);
        return sig_add(fft1d(xe, N, d+1, exp), sig_mul(fft1d(xo, N, d+1, exp), W));
    }
}




sig dft1d(sig const& x, unsigned long N, unsigned long d, sig* &exp) {
    
    unsigned long len = x.N;
    if(exp == NULL) {                       //  calculate the complex exponents if not already calculated
        exp = new mdsig;                    //  initialise exp as mdsig;
        (*(mdsig*)exp).data = new sig[N]; //  create N uni-dimensional signals (dimension of k in dft loop)
        for(unsigned long k=0; k<N; k++) {
            (*(mdsig*)exp).data[k].re = new double[len];
            (*(mdsig*)exp).data[k].im = new double[len];
            for(unsigned long n=0; n<len; n++) {
                (*(mdsig*)exp).data[k].re[n] = std::cos(TWOPI * (double)k * std::pow(2, d)*(double)n / (double)N);
                (*(mdsig*)exp).data[k].im[n] = -std::sin(TWOPI * (double)k * std::pow(2, d)*(double)n / (double)N);
            }
            (*(mdsig*)exp).data[k].N = len; //  set length of uni-dimensional signal (dim.of n in loop)
        }
        (*exp).N = N;                       //  set length of dimension of k
    }    
    sig X;
    X.N = N;
    X.re = new double[N];
    X.im = new double[N];
    for(unsigned long k=0; k<N; k++) {
        X.re[k] = 0;
        X.im[k] = 0;
    }
    std::cout<<"X initialised\n";
    //  perform DFT:
    for(unsigned long k=0; k<N; k++) {
        for(unsigned long n=0; n<len; n++) {
            // ac - bd:
            X.re[k] += (x.re[n] * (*(mdsig*)exp).data[k].re[n]) - (x.im[n] * (*(mdsig*)exp).data[k].im[n]);
            // ad + bc
            X.im[k] += (x.re[n] * (*(mdsig*)exp).data[k].im[n]) - (x.im[n] * (*(mdsig*)exp).data[k].re[n]);
        }
    }

    return X;
}

/*    unsigned long len = x.N;
    
    if(exp == NULL) {
        //sig1d* exps = new sig1d[N];     // bins
        exp = new ndsig;
        (*(ndsig*)exp).data = new sig[len];
            

        for(unsigned long k=0; k<len; k++) {

            // init double[]
            (*(sig1d*)((*exp).data+k)).re = new double[len];
            (*(sig1d*)((*exp).data+k)).im = new double[len];
            for(unsigned long n=0; n<len; n++) {
                (*(sig1d*)((*exp).data+k)).re[n] = std::cos(TWOPI * (double)k * std::pow(2, d)*(double)n / (double)N);
                (*(sig1d*)((*exp).data+k)).im[n] = -std::sin(TWOPI * (double)k * std::pow(2, d)*(double)n / (double)N);
            }
            (*(sig1d*)((*exp).data+k)).N = len;
        }
        (*exp).N = N;
    }
    sig X;
    sig1d Xdat;
    Xdat.re = new double[N];
    Xdat.im = new double[N];
    Xdat.N = N;
    X.data = &Xdat;
    X.N = 1;
    
    for(unsigned long k=0; k<N; k++) {
        (*(sig1d*)X.data).re[k] = 0;
        (*(sig1d*)X.data).im[k] = 0;
        for(unsigned long n=0; n<len; n++) {
            (*(sig1d*)X.data).re[k] += (*(sig1d*)x.data).re[n] * (*(sig1d*)((*exp).data+k)).re[n] - (*(sig1d*)x.data).im[n] * (*(sig1d*)((*exp).data+k)).im[n];
            (*(sig1d*)X.data).im[k] += (*(sig1d*)x.data).re[n] * (*(sig1d*)((*exp).data+k)).im[n] + (*(sig1d*)x.data).im[n] * (*(sig1d*)((*exp).data+k)).re[n];
        }    
    }
*/
