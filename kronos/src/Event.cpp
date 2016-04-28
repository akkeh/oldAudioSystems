#include <iostream>
#include <cstdlib>
#include "KRNS_Event.h"
#include "KRNS_Track.h"
#include "KRNS.h"

void Event::print() {
    std::cout << "t: " << t << std::endl;
    std::cout << "\tprev: ";
    if(prev)
        std::cout << "Y";
    else
        std::cout << "N";
    std::cout << "\t next: ";
    if(next)
        std::cout << "Y";
    else
        std::cout << "N";
    std::cout << std::endl;
};

void Event::process(){
    std::cout << "processing with: " << argc << " arguments\n";
    print();
    track->funcCall(func_id, argc, argv);
};

void Event::run(Clock_t* clock) {
    /*
        run() will make an event evaluate the clock untill it is time.
        -   clock:  the clock to use
    */
    if((clock->get_time()) >= t) {    // is it time?
        process();
        if(next)
            next->run(clock);   // call next event
    } else {
        this->run(clock);   // re-call function
    }

};

int Event::add_Event(Event* newEvent, int direction) {
    switch(direction) {
        case -1:
            if(*newEvent < this)
                if(prev)
                    prev->add_Event(newEvent, -1);
                else
                    prepend(newEvent);
            else
                append(newEvent);
            break;
        case 1:
            if(*newEvent > this)
                if(next)
                    next->add_Event(newEvent, 1);
                else
                    append(newEvent);
            else
                prepend(newEvent);
            break;
        default:
            if(*newEvent > this)
                add_Event(newEvent, 1);
            else
                add_Event(newEvent, -1);
            break;
    };
};

int Event::prepend(Event* newEvent) {
    // links from newEvent:
    newEvent->set_prev(this->prev);
    newEvent->set_next(this);

    // link from this->prev
    if(prev)
        this->prev->set_next(newEvent);

    // link from this:
    this->prev = newEvent;

    return 0;
};

int Event::append(Event* newEvent) {
    // links from newEvent:
    newEvent->set_prev(this);
    newEvent->set_next(this->next);

    // link from this->next:
    if(next)
        this->next->set_prev(newEvent);

    // link from this:
    this->next = newEvent;

    return 0;
};

void Event::clean() {
    prev->set_next(next);
    next->set_prev(prev);
    next->clean();
    delete this;
};

Event::Event(unsigned long t_t, int t_func_id, Track* t_track, int t_argc, void** t_argv, bool t_isTemp) 
    : t(t_t), func_id(t_func_id), track(t_track), argc(t_argc), argv(t_argv), isTemp(t_isTemp) {
    prev = NULL;
    next = NULL;
};

Event::~Event() {
};
