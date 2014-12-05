#ifndef ZTRANS_H
#define ZTRANS_H

// common procedures:
struct sig zero_pad(sig const& in_file, long int N, int print = 0);

struct sig dft(sig const& in_sig, int print = 0);
struct sig idft(sig const& in_sig, int print = 0);

struct sig fft(sig const& in_sig, unsigned long int N, int print = 0, 
                double* rexp = NULL, double* iexp = NULL,
                unsigned long int depth = 0);

void dft_rec(double* r_in, unsigned long int N, int print, 
                double* real, double* imag, 
                unsigned long int depth, double* rexp, double* iexp);
#endif
