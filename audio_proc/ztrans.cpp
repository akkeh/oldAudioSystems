#include <cmath>
#include <complex>
#include <fstream>
#include "audioproc.h"
#include "ztrans.h"

struct sig zero_pad(sig const& in_sig, long int N, int print) {
    long int length = in_sig.length;
    if(N > length) {
        sig out_sig;
        double out_rdata[N];
        double out_idata[N];
        long int i;
        for(i=0; i<length; i++) {
            out_rdata[i] = in_sig.rdata[i];
            out_idata[i] = in_sig.idata[i];
        }
        if(print == 1) printf("wrote %li samples\n", i);
        for(i=i; i<N; i++) {
            out_rdata[i] = 0.0;
            out_idata[i] = 0.0;
        }
        if(print == 1) printf("padded %li samples; new length: %li\n", N-length, N);
        out_sig.rdata = out_rdata;
        out_sig.idata = out_idata;
        out_sig.length = N;
        out_sig.chn_num = in_sig.chn_num;
        out_sig.fs = in_sig.fs;
        return out_sig;
    } else {
        printf("N < length!\n");
        return in_sig;
    }
}
