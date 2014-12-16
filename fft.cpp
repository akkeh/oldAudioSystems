#include "azath.h"
#include "ztrans.h"
#include <iostream>

void dft1d(sig const& x, unsigned long N, sig* &X, unsigned long d, sig* &exp) {
    
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
    if(X == NULL) {                     //  initialise output buffer if not already initialised
        X = new sig;
        (*X).N = N;
        (*X).re = new double[N];
        (*X).im = new double[N];
        for(unsigned long k=0; k<N; k++) {
            (*X).re[k] = 0;
            (*X).im[k] = 0;
        }
    }
    std::cout<<"X initialised\n";
    //  perform DFT:
    for(unsigned long k=0; k<N; k++) {
        for(unsigned long n=0; n<len; n++) {
            // ac - bd:
            (*X).re[k] += (x.re[n] * (*(mdsig*)exp).data[k].re[n]) - (x.im[n] * (*(mdsig*)exp).data[k].im[n]);
            // ad + bc
            (*X).im[k] += (x.re[n] * (*(mdsig*)exp).data[k].im[n]) - (x.im[n] * (*(mdsig*)exp).data[k].re[n]);
        }
    }


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
