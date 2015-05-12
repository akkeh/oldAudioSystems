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

int Event::append(Event* new_event) {


};  // Event::add();

int Event::prepend(Event* new_event) {

};  // Event::prepend();
