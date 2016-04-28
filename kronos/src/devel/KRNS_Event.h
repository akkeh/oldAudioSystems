#ifndef KRNS_EVENT_H_
#define KRNS_EVENT_H_

#include "KRNS.h"
#include "KRNS_Track.h"

class Event {
public:
    Event(unsigned long t_t, Track* t_track, int t_argc = 0, void** t_argv = NULL, bool t_isTemp = false);
    ~Event();
    
    virtual void process() = 0;
    void run(Clock_t* clock);

    unsigned long get_time() { return t; };
    void clean();

    // debug:
    void print();

    // linkes list stuff:
    int add_Event(Event* newEvent, int direction = 0);
    Event* get_prev() { return this->prev; };
    Event* get_next() { return this->next; };
    void set_prev(Event* newEvent) { this->prev = newEvent; };
    void set_next(Event* newEvent) { this->next = newEvent; };

    // overloads:
    inline bool operator< (Event* b) {
        return this->t < b->get_time();
    };
    inline bool operator> (Event* b) {
        return this->t > b->get_time();
    };

protected:
    unsigned long t;    // timestamp
    int func_id;
    Track* track;
    int argc;
    void** argv;

    // linked list stuf:
    Event* prev;
    Event* next;
    inline int prepend(Event* newEvent);
    inline int append(Event* newEvent);

    bool isTemp;
};

#endif
