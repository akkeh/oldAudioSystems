#ifndef AUDIOPROC_H
#define AUDIOPROC_H

struct wave{
    double* data;
    unsigned int length;
    unsigned short chn_num;
    unsigned int fs;
};

struct wave read(const char* filename, int print = 0);
int write(const char* filename, wave const& in_data, unsigned short bps = 16, int print = 0);

struct wave normalise(wave const& in_wave, int print = 0);


#endif
