#include <cmath>
#include <cstdlib>

#include "ztrans.h"

#ifndef AZATH_H_
#define AZATH_H_

#define FS 44100
#define TWOPI M_PI+M_PI
struct sig {
    sig* data;
    unsigned long N;
};
struct sig1d : public sig {
    double* re;
    double* im;
    unsigned long N;
};

sig read(const char* filename, int print = 0);
int write(const char* filename, sig const& in_sig, int print = 0);

#endif
