#include <string.h>
#include <fstream>
#include <cmath>
#include "simpleproc.h"
#include "audioproc.h"
/*
||  functions revolving around chaning the amplitudes of sounds:
    -   normalise
    -  
|| 
*/

sig normalise(sig const& in_sig, int print) {
    sig out_sig;
	int length = in_sig.length;
    double out_data[length];
    
    double max_val;
    for(int n=0; n<length; n++) {
        double sample = d_abs(in_sig.rdata[n]);
        if(sample > max_val) {
            if(print==1) printf("old max.: %f\t new max.: %f\n", max_val, sample);
            max_val = sample; 
        }
    }
    if(print == 1) printf("peak: %f; %fdB\n", max_val, 20*std::log(max_val));


    for(int n=0; n<length; n++) {
        out_data[n] = in_sig.rdata[n]/max_val;
    }

    out_sig.rdata = out_data;
    out_sig.idata = in_sig.idata;
    out_sig.chn_num = in_sig.chn_num;
    out_sig.length = length;
    out_sig.fs = in_sig.fs;

    return out_sig;
}

