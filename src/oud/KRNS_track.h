#ifndef KRNS_TRCK_H_
#define KRNS_TRCK_H_

#include "KRNS_loadlib.h"

class Track;

#include "KRNS_event.h"
#include "KRNS_sched.h"

class Track {
public:
    virtual void add_event(unsigned long t0, unsigned long dur);
    virtual void eval(unsigned long t); // must something be done?
    virtual void* output(unsigned long t);  // do it
     
protected:
    char* lib_name;
    TrackLib* lib;   // .so file handler
    void load_lib();

    // Event list (linked list): -----------------|
    unsigned long event_c;
    Event* begin;
    Event* end;
    Event* last;    // last added event
    Event* current; // event to be evaluated next
    // -------------------------------------------|

    // memory:
    unsigned char mem_i;    // output buffer write pointer
    void* mem_output[256];      // output memory buffer
    unsigned long intern_t;    // internal time (i.e. last 't' from call to output())

    // links:
    Track* inputs;
    int inp_c;
   
    Sched* scheduler;
   
    // graphic stuff:
 
};

#endif
