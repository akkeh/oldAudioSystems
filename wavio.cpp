#include <string.h>
#include <fstream>
#include <cmath>
#include "audioproc.h"

/*
||  functions to read/write .wav files
||      read(const char* filename, int print = 0)
            read a *.wav file and put data in struct sig file
            return: struct sig
||      write(const char* filename, sig const& in_data, unsigned short bps = 16, int print = 0)
            writes data from struct sig to .wav file
            return: int

||
	use long int for data-length
||
*/

struct sig read(const char* filename, int print) {
    int error = -1;
    FILE* infile=fopen(filename, "rb");
    if(!infile) { printf("file %s not found", filename); goto exit; }

    //RIFF
    char ck1_id[5];
    unsigned int ck1_size;
    char wave_id[5];
    //fmt
    char ck2_id[5];
    unsigned int ck2_size;
    unsigned short fmt;
    unsigned short chn_num;
    unsigned int fs;
    unsigned int avg_bps;    //fs*(bps/8)*chn_num
    unsigned short blk_all;
    unsigned short bps;      //bytes_per_sample*8 (16-bit=2*8)
    //data
    char ck3_id[5];
    unsigned int ck3_size;   //(bps/8)*chn_num*samples
    short* in_data;    //N = ck3_size;
    double* data;
	double* init_data;
    short bit_depth;
    int size;

    //RIFF
    fread(ck1_id, sizeof(char), 4, infile);
    ck1_id[4]='\0';
    if(!strcmp(ck1_id, "RIFF ")) { printf("file %s not a RIFF: %s\n", filename, ck1_id); goto exit; }
    if(print == 1) printf("ck_id: %s\n", ck1_id);

    fread(&ck1_size, sizeof(unsigned int), 1, infile);
    if(print == 1) printf("ck1_size: %i\n", ck1_size);

    fread(wave_id, sizeof(char), 4, infile);
    wave_id[4]='\0';
    if(!strcmp(wave_id, "WAVE ")) {printf("file %s not a WAVE: %s", filename, wave_id); goto exit; }
    if(print == 1) printf("wave_id: %s\n", wave_id);

    //fmt
    fread(ck2_id, sizeof(char), 4, infile);
    ck2_id[4]='\0';
    if(!strcmp(ck2_id, "fmt  ")) {printf("subchunk 2 id wrong: %s\n", ck2_id); goto exit; }
    if(print == 1) printf("ck2_id: %s\n", ck2_id);

    fread(&ck2_size, sizeof(unsigned int), 1, infile);
    if(print == 1) printf("ck2_size: %i\n", ck2_size);

    fread(&fmt, sizeof(unsigned short), 1, infile);
    if(fmt != 1) printf("WARNING: file compressed: %i\n", fmt);
    if(print == 1) printf("file format: %i\n", fmt);

    fread(&chn_num, sizeof(unsigned short), 1, infile);
    if(print == 1) printf("channels: %i\n", chn_num);

    fread(&fs, sizeof(unsigned int), 1, infile);
    if(print == 1) printf("samplerate: %i\n", fs);

    fread(&avg_bps, sizeof(unsigned int), 1, infile);
    if(print == 1) printf("average bits per second: %i\n", avg_bps);

    fread(&blk_all, sizeof(unsigned short), 1, infile);
    if(print == 1) printf("blockallign: %i\n", blk_all);

    fread(&bps, sizeof(unsigned short), 1, infile);
    if(print == 1) printf("bits per second: %i\n", bps);

    //data
    fread(ck3_id, sizeof(char), 4, infile);
    ck3_id[4]='\0';
    if(!strcmp(ck3_id, "data ")) {printf("data chunk missing? %s\n", ck3_id); goto exit; }
    if(print ==1) printf("ck3_id: %s\n", ck3_id);

    fread(&ck3_size, sizeof(unsigned int), 1, infile);
    size = ck3_size/2;
    if(print == 1) printf("Amount of blocks: %i;\t samples: %i\n", ck3_size, size);

    //check justness of gained values:
    if(avg_bps != (fs*(bps/8)*chn_num)) {printf("avg_bps == (fs*(bps/8)*chn_num) check failed!\n"); goto exit; }
    else if(print == 1) printf("avg_bps == (fs*(bps/8)*chn_num)\n");
    if(blk_all != ((bps/8)*chn_num)) {printf("blk_all == ((bps/8)*chn_num) check failed!\n"); goto exit; }
    else if(print == 1) printf("blk_all == ((bps/8)*chn_num)\n");

	bit_depth = (std::pow(2, 16)/2-1);
    if(print == 1) printf("bitdepth: %i", bit_depth);
    in_data = new short[size];
    data = new double[size];

    //samples:
    for(int n=0; n<size; n++) {
        fread(&in_data[n], sizeof(short), 1, infile);
        data[n] = double(in_data[n])/bit_depth;
    }

    error = 0;
    exit:
    fclose(infile);
    if(error == 0) {
        if(print == 1) printf("loaded %s, %i samples\n", filename, size);
        sig output;
        output.rdata = data;
        output.idata = NULL;
        output.length = size;
        output.chn_num = chn_num;
        output.fs = fs;
        
        delete[] in_data;

        return output;
    }
}

int write(const char* filename, sig const& in_data, unsigned short bps, int print) {
    int error = -1;
    FILE* outfile=fopen(filename, "wb");
    if(!outfile) { printf("file %s not found", filename);}

    unsigned int ck3_size = in_data.length * 2;
    unsigned int size = ck3_size/2;
    //RIFF
    unsigned int ck1_size = 4 + 24 + 8 + ck3_size;
    //fmt
    unsigned int ck2_size = 16;
    unsigned short fmt = 1;
    unsigned short chn_num = in_data.chn_num;
    unsigned int fs = in_data.fs;
    unsigned int avg_bps = fs*(bps/8)*chn_num;   //fs*(bps/8)*chn_num
    unsigned short blk_all = (bps/8)*chn_num;  //bps*chn_num
    //data
	short* out_data = new short[size];    //N = ck3_size;
    double* f_data = in_data.rdata;

	short bit_depth = (std::pow(2, 16)/2-1);
    //RIFF
    fwrite("RIFF ", sizeof(char), 4, outfile);
    if(print == 1) printf("wrote header1 to file: RIFF\n");
    fwrite(&ck1_size, sizeof(unsigned int), 1, outfile);
    if(print == 1) printf("wrote ck1_size to file: %i\n", ck1_size);
    fwrite("WAVE ", sizeof(char), 4, outfile);
    if(print == 1) printf("wrote tag to file: WAVE\n");

    //fmt
    fwrite("fmt  ", sizeof(char), 4, outfile);
    if(print == 1) printf("wrote fmt-tag to file: fmt\n");
    fwrite(&ck2_size, sizeof(unsigned int), 1, outfile);
    if(print == 1) printf("wrote ck2_size to file: %i\n", ck2_size);
    fwrite(&fmt, sizeof(unsigned short), 1, outfile);
    if(print == 1) printf("wrote fmt to file: %i\n", fmt);
    fwrite(&chn_num, sizeof(unsigned short), 1, outfile);
    if(print == 1) printf("wrote chn_num to file: %i\n", chn_num);
    fwrite(&fs, sizeof(unsigned int), 1, outfile);
    if(print == 1) printf("wrote fs to file: %i\n", fs);
    fwrite(&avg_bps, sizeof(unsigned int), 1, outfile);
    if(print == 1) printf("wrote avg_bps to file: %i\n", avg_bps);
    fwrite(&blk_all, sizeof(unsigned short), 1, outfile);
    if(print == 1) printf("wrote blk_all to file: %i\n", blk_all);
    fwrite(&bps, sizeof(unsigned short), 1, outfile);
    if(print == 1) printf("wrote bps to file: %i\n", bps);

    //data
    fwrite("data ", sizeof(char), 4, outfile);
    if(print == 1) printf("wrote data-tag to file: data\n");
    fwrite(&ck3_size, sizeof(unsigned int), 1, outfile);
    if(print == 1) printf("wrote ck3_size to file: %i\n", ck3_size);

    double sample;
    for(int n=0; n<size; n++) {
        sample = (f_data[n]) * bit_depth;
        out_data[n] = (short)sample;
        fwrite(&out_data[n], sizeof(short), 1, outfile);
    }

    fclose(outfile);
    return 0;

}
