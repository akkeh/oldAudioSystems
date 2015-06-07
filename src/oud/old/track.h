#ifndef KRNS_TRCK_H_
#define KRNS_TRCK_H_

class Track;

#include "event.h"
#include "sched.h"

class Track {
public:
    void add_event(unsigned long t0, unsigned long dur);
    void eval(unsigned long t);
    void output(unsigned long t);
 
protected:
    void* sofile;   // .so file handler

    // Event list (linked list):
    unsigned long event_c;
    Event* begin;
    Event* end;
    Event* last;    // last added event
    Event* current; // event to be evaluated next

    // function defs:
    typedef void* (*proc_t)(int argc, const char** argv);
    typedef int (*msg_t)(int argc, const char** argv);
    typedef int (*spawn_t)(int argc, const char** argv);
    typedef int (*kill_t)(int argc, const char** argv);
    proc_t proc;
    msg_t msg;
    spawn_t spawn;
    kill_t kill;

    // memory:
    unsigned char mem_i;    // output buffer write pointer
    void* mem_output[256];      // output memory buffer
    unsigned long intern_t;    // internal time (i.e. last 't' from call to output())

    // state:
    int argc;
    char** argv;

    // links:
    Track* inputs;
    int inp_c;
   
    Sched* scheduler;
   
    // graphic stuff:
 
};


template <class T> class templTrack : public Track {
private:
    // function defs:

    // memory:
};

#endif
