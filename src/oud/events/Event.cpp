
#include <iostream>
#include <cstdlib>
#include "KRNS_event.h"
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

void* Event::process(){
    print();
    return procFunc(argc, argv);
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

Event::Event(unsigned long t_t, func_t t_procFunc, int t_argc, void** t_argv) 
    : t(t_t), procFunc(t_procFunc), argc(t_argc), argv(t_argv) {
    prev = NULL;
    next = NULL;
};


int main() {
    Event* strt = new Event(0);
    Event* a = new Event(10);
    Event* b = new Event(2);
    Event* c = new Event(20);
    strt->add_Event(a);
    strt->add_Event(b);
    strt->add_Event(c);


    Event* last = strt;

    strt->run(new Clock_t(OFFLINE, 0));

    


};
