#include "azath.h"
#include "ztrans.h"

void dft1d(sig const& x, unsigned long N, sig* X, unsigned long d, sig* exp) {
    unsigned long len = (*(sig1d*)x.data).N;
    if(exp == NULL) {
        sig1d* exps = new sig1d[N];     // bins
        for(unsigned long k=0; k<N; k++) {
            exps[k].re = new double[len];
            exps[k].im = new double[len];
            for(unsigned long n=0; n<len; n++) {
                exps[k].re[n] = std::cos(TWOPI * (double)k * std::pow(2, d)*(double)n / (double)N);
                exps[k].im[n] = -std::sin(TWOPI * (double)k * std::pow(2, d)*(double)n / (double)N);
            }
            exps[k].N = len;
        }
        (*exp).data = exps;
        (*exp).N = N;
    }
    
    for(unsigned long k=0; k<N; k++) {
        for(unsigned long n=0; n<len; n++) {
            (*(sig1d*)(*X).data).re[n] += (*(sig1d*)x.data).re[n] * (*(sig1d*)((*exp).data+k)).re[n] - (*(sig1d*)x.data).im[n] * (*(sig1d*)((*exp).data+k)).im[n];
            (*(sig1d*)(*X).data).im[n] += (*(sig1d*)x.data).re[n] * (*(sig1d*)((*exp).data+k)).im[n] + (*(sig1d*)x.data).im[n] * (*(sig1d*)((*exp).data+k)).re[n];
        }    
    }
}
