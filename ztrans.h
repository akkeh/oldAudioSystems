#ifndef ZTRANS_H
#define ZTRANS_H

struct plr{
    double mag;
    double phase;
};
struct crt{
    double rl;
    double im;
};

// common procedures:
struct sig zero_pad(sig const& in_file, long int N, int print = 0);

struct sig dft(sig const& in_sig, int print = 0);
struct sig idft(sig const& in_sig, int print = 0);
#endif
