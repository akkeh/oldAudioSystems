#include "event.h"
// function defs:
typedef 

//


class Track {
public:

private:
    void* sofile;   // .so file handler
    


    // Event list (linked list):
    unsigned long event_c;
    Event* begin;
    Event* end;
    Event* last;    // last added event




    // state:
    int argc;
    char** argv;


};
