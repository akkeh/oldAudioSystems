#ifndef ZTRANS_H_
#define ZTRANS_H_

#include "azath.h"

sig fft(sig const& x);
sig dft1d(sig const& x, unsigned long N, unsigned long d);
sig fft1d(sig const& x, unsigned long N, unsigned long d, sig* &W);

#endif

