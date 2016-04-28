#include "azath.h"
#include <iostream>

int main() {
    sig test;
    sig1d dat;
    double* real = new double[8];
    double* imag;
    for(int n=0; n<8; n++) {
        real[n] = std::pow(-1, n % 2);
    }
    imag = NULL;
    dat.re = real;
    dat.im = imag;
    dat.N = 8;
    std::cout<<"data set\n";
    test.N = 1;
    test.data = &dat;

    for(int s=0; s<test.N; s++) {
        for(int n=0; n<(*(sig1d*)test.data).N; n++) {
            std::cout<<"dim: "<<s<<" sample: "<<n<<" val:\n\t";
            std::cout<<(*(sig1d*)test.data).re[n]<<std::endl;
        }
    }
}
