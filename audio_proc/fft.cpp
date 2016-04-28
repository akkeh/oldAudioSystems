#include <cmath>
#include <fstream>
#include "simpleproc.h"
#include "audioproc.h"
#include "ztrans.h"

#define 2PI = M_PI+M_PI

sig dft_rec(double* re_in, double* im_in, unsigned long int N,
            double* re_out, double* im_out
