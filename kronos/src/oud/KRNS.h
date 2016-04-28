#ifndef KRNS_H_
#define KRNS_H_
#include <ctime>

typedef void* (*func_t)(int, void*);    // function tupe
void* nullFunc(int a, void** ) {};

class Clock_t {
public:
    Clock_t(int type) : clock_type(type), t(0){};
    unsigned long get_time() {
        switch(clock_type) {
        case 0: // clock();
            return clock();
            break;
        case 1: // simple counter
            return t++;
        };
    };
private:
    int clock_type;
    unsigned long t;
};


// includes:
#include "KRNS_Event.h"

#endif
