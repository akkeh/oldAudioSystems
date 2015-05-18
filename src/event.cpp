#include "event.h"
#include <cstdlib>

int Event::add(Event* new_event, bool reversed){
    /*
        Add event to linked list
        -   reverse: 
            -   false: search normal direction
            -   true: search reversed direction
    */
    if(!reversed) {
        // normal:
        if(new_event > this) {
            if(next) next->add(new_event, reversed);
            else return -1; // should not happen!
        } else prepend(new_event);
    } else {
        // reversed:
        if(new_event < this) {
            if(prev) prev->add(new_event, reversed);
            else return -1; // should not happen!
        } else append(new_event);
    }
    return 0;
}
    
unsigned long Event::get_t0() {
    return t0;
}
    
inline void Event::do_func(unsigned long t) {
   
}

int Event::append(Event* new_event) {
    new_event->prev = this;
    new_event->next = this->next;
    this->next = new_event;
    return 0;
}

int Event::prepend(Event* new_event) {
    new_event->prev = this->prev;
    new_event->next = this;
    this->prev = new_event;
    return 0;
}
    
Event::Event(int t_argc, const char** t_argv, unsigned long t_t0, unsigned long t_tT){ 
    t0 = t_t0; tT = t_tT;
    next = prev = NULL;
    argc = t_argc;
    argv = t_argv;

}
