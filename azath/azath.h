#ifndef AZATH_H_
#define AZATH_H_
#include <cstdlib>
#include <cmath>

#define FS 44100
#define TWOPI (M_PI+M_PI)
struct sig {
    double* re;
    double* im;
    unsigned long N;
    virtual ~sig() { delete[] re; delete[] im; };
};// uni-dimenstional signal

struct mdsig : public sig {
    sig* data;
    unsigned long N;
//    ~mdsig() { delete[] data; };
};// multi dimensional signal

sig read(const char* filename, int print = 0);
int write(const char* filename, sig const& in_sig, int print = 0);

#include "simpleproc.h"
#include "ztrans.h"


#endif
