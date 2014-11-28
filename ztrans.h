#ifndef ZTRANS_H
#define ZTRANS_H

// common procedures:
struct sig zero_pad(sig const& in_file, long int N, int print = 0);

struct sig dft(sig const& in_sig, int print = 0);
struct sig idft(sig const& in_sig, int print = 0);

struct sig fft(sig const& in_sig, int print = 0);
#endif
