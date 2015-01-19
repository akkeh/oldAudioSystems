#ifndef SPROC_H_
#define SPROC_H_

#include "azath.h"
//  common procedures:
void c_mul(double a, double b, double c, double d, double* re, double* im);

//  sig procedures:
void arrange(sig const& x, sig* buf, unsigned long int id);
sig decimate(sig const& x, int odd);
sig sig_add(sig const& sig1, sig const& sig2);
sig sig_mul(sig const& sig1, sig const& sig2);

#endif
