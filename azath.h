#include <cmath>
#include <cstdlib>

#include "ztrans.h"

#ifndef AZATH_H_
#define AZATH_H_

#define FS 44100
#define TWOPI (M_PI+M_PI)
struct sig {
    double* re;
    double* im;
    unsigned long N;
};// uni-dimenstional signal

struct mdsig : public sig {
    sig* data;
    unsigned long N;
};// multi dimensional signal

sig read(const char* filename, int print = 0);
int write(const char* filename, sig const& in_sig, int print = 0);

#endif
