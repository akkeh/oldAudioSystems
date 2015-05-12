#include "event.h"

#ifndef KRNS_TRACK_H_
#define KRNS_TRACK_H_

// function prototypes:
typedef void* (*process_t)();
typedef int (*add_event_t)();
typedef int (*msg_t)();
typedef int (*spawn_t)();

class Track {
public:
    int load_so(const char* sofile);
    void* output(unsigned long t);

private:
    void* solib;
    Track* input;
    Event* events;
    unsigned long last_t;
    void* last_output;

    // methods:
    void* process(unsigned long t);
    process_t process_f;
    add_event_t add_event;
    msg_t msg;
    spawn_t spawn;

};  // class Track;

#endif
