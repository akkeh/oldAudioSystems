#ifndef KRNS_SCHD_H_
#define KRNS_SCHD_H_

class Sched;
#include "KRNS_track.h"

class Sched {
public:
    int add_track();
    int render();   // pre-process
    int run();      // render() must be called first
    int stop();

private:
    int play();         // play loop
    unsigned long t;    // play time

    int eval_track(int track_i);    // evaluate tracks

    unsigned long track_c;  // track count
    Track* tracks;          // tracks
    
    // graphic stuff:
    
};

#endif
