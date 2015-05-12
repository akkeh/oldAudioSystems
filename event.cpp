#include "event.h"

int Event::add(Event* new_event, int rev) {
    /*
        add event to list
        -   rev: 0 normal; 1: reversed
    */
    if(rev == 0) {  // normal
        if(new_event > this) {
            if(next) next->add(new_event, rev);
            else return -1; // should not happen
        } else prepend(new_event);
    } else {
        if(new_event < this) {
            if(prev) prev->add(new_event, rev);
            else return -1; // should not happen
        } else append(new_event);
    }
    return 0;
};  // Event::add();

int Event::prepend(Event* new_event) {
    // prepend new_event before this
    new_event->prev = this->prev;
    new_event->next = this;
    this->prev = new_event;
    return 0;
};  // Event::prepend();

int Event::append(Event* new_event) {
    // append new_event after this 
    new_event->prev = this;
    new_event->next = this->next;
    this->next = new_event;
    return 0;
};  // Event::add();


unsigned long Event::get_startt() {
    return start_t;
}
