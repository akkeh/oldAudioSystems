#include "simpleproc.h"
#include <cmath>
#include <iostream>



void c_mul(double a, double b, double c, double d, double* re, double* im) {
    *re = a*c - b*d;
    *im = a*d + b*c;
}

double c_abs(double a, double b) {
    return std::sqrt(a*a + b*b);
}

void arrange(sig const& x, sig* buf, unsigned long int id) {
    if(x.N > 1) {
        arrange(decimate(x, 0), buf, id);    
        arrange(decimate(x, 1), buf, id+x.N/2);
    } else {
        (*buf).re[id] = x.re[0];
        (*buf).im[id] = x.im[0];
    }
}

sig decimate(sig const& x, int odd) {
    sig out;
    out.re = new double[x.N/2];
    out.im = new double[x.N/2];

    for(unsigned long n=0; n<x.N/2; n++) {
        out.re[n] = x.re[2*n+odd];
        out.im[n] = x.im[2*n+odd];
    }

    out.N = x.N/2;
    return out;
}

sig sig_add(sig const& sig1, sig const& sig2) {
    if(sig1.N != sig2.N) {
        std::cout<<"sig add: lengths incompatible!\n";
        return sig1;
    }
    sig out;
    out.re = new double[sig1.N];
    out.im = new double[sig1.N];
    for(unsigned long n=0; n<sig1.N; n++) {
        out.re[n] = sig1.re[n]+sig2.re[n];
        out.im[n] = sig1.im[n]+sig2.im[n];
    }
    out.N = sig1.N;
    return out;
}

sig sig_mul(sig const& sig1, sig const& sig2) {
    if(sig1.N != sig2.N) {
        std::cout<<"sig mul: lengths incompatible!\n"<<"\tN1: "<<sig1.N<<"\tN2: "<<sig2.N<<std::endl;
        return sig1;
    }
    sig out;
    out.re = new double[sig1.N];
    out.im = new double[sig1.N];
    for(unsigned long n=0; n<sig1.N; n++) {
        c_mul(
                sig1.re[n], sig1.im[n], 
                sig2.re[n], sig2.im[n],
                &out.re[n], &out.im[n]
        );
    }
    out.N = sig1.N;
    return out;
}
