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

wave normalise(wave const& in_wave, int print) {
    wave out_wave;
	int length = in_wave.length;
    double out_data[length];
    
    double max_val;
    for(int n=0; n<length; n++) {
        double sample = d_abs(in_wave.data[n]);
        if(sample > max_val) {
            if(print==1) printf("old max.: %f\t new max.: %f\n", max_val, sample);
            max_val = sample; 
        }
    }
    if(print == 1) printf("maximum: %f\n", max_val);

    for(int n=0; n<length; n++) {
        out_data[n] = in_wave.data[n]/max_val;
    }

    out_wave.data = out_data;
    out_wave.chn_num = in_wave.chn_num;
    out_wave.length = length;
    out_wave.fs = in_wave.fs;

    return out_wave;
}

