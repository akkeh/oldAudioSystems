#ifndef AUDIOPROC_H
#define AUDIOPROC_H

struct sig{
    double* rdata;
    double* idata;
    unsigned long length;
    unsigned short chn_num;
    unsigned int fs;
};

struct sig read(const char* filename, int print = 0);
int write(const char* filename, sig const& in_data, unsigned short bps = 16, int print = 0);

struct sig normalise(sig const& in_sig, int print = 0);

sig convolve(const sig* sig1, const sig* sig2, int print = 0);
#endif
