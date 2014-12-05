#include <cmath>
#include <fstream>
#include "simpleproc.h"
#include "audioproc.h"

sig convolve(const sig* sig1, const sig* sig2, int print) {
    
    if((*sig1).fs != (*sig2).fs) return *sig1;
    sig out_sig;

    unsigned long int N = (*sig1).length;
    unsigned long int M = (*sig2).length;
    double* data = new double[M+N];
    out_sig.length = N;
    out_sig.fs = (*sig1).fs;
    out_sig.chn_num = 1;
    
    for(unsigned long int n=0; n<N; n++) {
        if(print == 1) printf("convolving: %f %s\n", 100/(double)N*(double)n, "%");
        for(unsigned long int m=0; m<M; m++) {
            data[n+m]= (data[n+m] + ((*sig1).rdata[n] * (*sig2).rdata[m]));
        }
    }
    out_sig.rdata = data;
    out_sig.idata = NULL;
    
    

    return normalise(out_sig);
}
