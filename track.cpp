#include <dlfcn.h>
#include <iostream>
#include "track.h"

int Track::load_so(const char* sofile) {
    solib = dlopen(sofile, RTLD_NOW);    // open so file
    if(!solib) {                                // check if lib opened
        std::cerr << "\nlib. " << sofile << " could not be opened!\n";
        return -1;
    };
    dlerror();  // reset errors
    
    // load process():
    process_f = (process_t) dlsym(solib, "process");
    if(dlerror()) {
        std::cerr << "\nfunction 'process' not found!\n";
    }
    
    // load add_event():
    add_event = (add_event_t) dlsym(solib, "add_event");
    if(dlerror()) {
        std::cerr << "\nfunction 'add_event' not found!\n";
    }

    // load msg():
    msg = (msg_t) dlsym(solib, "msg");
    if(dlerror()) {
        std::cerr << "\nfunction 'msg' not found!\n";
    }

    // load spawn():
    spawn = (spawn_t) dlsym(solib, "spawn");
    if(dlerror()) {
        std::cerr << "\nfunction 'spawn' not found!\n";
    }
};  // Track::load_so();

void* Track::process(unsigned long t) {
    last_output = process_f();
    last_t = t;
    return last_output;
};  // Track::process();

void* Track::output(unsigned long t) {
    if(t == last_t) return last_output;
    return process(t);
};  // Track::output();



Track::Track() {
    first = last = NULL;
    event_count = 0;
};  // Track::Track();

Track::~Track() {
   
};  // Track::~Track();


