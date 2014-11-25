#include <cmath>
#include <complex>
#include <fstream>
#include "audioproc.h"
#include "ztrans.h"

sig dft(sig const& in_sig, int print) {     // now only monophonic!
    sig out_sig;
    unsigned long length = in_sig.length;
    double* rdata = new double[length];
    double* idata = new double[length];
    out_sig.length = length;

    out_sig.fs = in_sig.fs;
    out_sig.chn_num = in_sig.chn_num;

    double rval, ival, a, b, c, d;
    for(unsigned long int k=0; k<length; k++) {
        rval = 0;
        ival = 0;
        for(unsigned long int n=0; n<length; n++) {
            // calculate (a+bi) * (c+di):
            a = in_sig.rdata[n];
            b = in_sig.idata[n];
            c = std::cos(2.0*M_PI * (double)k * (double)n / length);
            d = -std::sin(2.0*M_PI * (double)k * (double)n / length);
            
            rval+=(a*c-d*b);
            ival+=(a*d+b*c);
        }
        rdata[k] = rval;
        idata[k] = ival;
    }

    out_sig.rdata = rdata;
    out_sig.idata = idata;
/*
    delete[] rdata;
    delete[] idata;
*/
    return out_sig;
}

sig idft(sig const& in_sig, int print) {
    sig out_sig;
    unsigned long length = in_sig.length;
    double* rdata = new double[length];
    double* idata = new double[length];
    out_sig.length = length;

    out_sig.fs = in_sig.fs;
    out_sig.chn_num = in_sig.chn_num;

    double rval, ival, a, b, c, d;
    for(unsigned long int n=0; n<length; n++) {
        rval = 0;
        ival = 0;
        for(unsigned long int k=0; k<length; k++) {
            // calculate (a+bi) * (c+di):
            a = in_sig.rdata[k];
            b = in_sig.idata[k];
            c = std::cos(2.0*M_PI * (double)k * (double)n / length);
            d = std::sin(2.0*M_PI * (double)k * (double)n / length);
            
            rval+=(a*c-d*b);
            ival+=(a*d+b*c);
        }
        rdata[n] = rval/length;
        idata[n] = ival/length;
    }

    out_sig.rdata = rdata;
    out_sig.idata = idata;
   
    return out_sig; 
}


/*
sig dft_depr(sig const& in_file, int print) {
    sig dft_out;
    unsigned long length = in_file.length;
    dft_out.data = new std::complex<double>[length];
    dft_out.length = length;
    
    std::complex<double> csin;
    std::complex<double> z;
    std::complex<double> bin;
    if(print==1) printf("length: %li\n", length);
    for(long int k=0; k<length; k++) {
        if(print==1) printf("done: %li;\tto go: %li\n", k, length-k);
        bin = 0 + 0i;
        for(long int n=0; n<length; n++) {
            z = -1i * 2*M_PI * k * n / length;
            csin = std::exp(z);
            bin+=in_file.data[n]*csin;
        }
        dft_out.data[k] = bin;
    }
    return dft_out;
}
*/
