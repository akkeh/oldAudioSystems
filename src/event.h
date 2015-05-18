#ifndef KRNS_EVNT_H_
#define KRNS_EVNT_H_

class Event {
public:
    int add(Event* new_event, bool reversed);
    
    unsigned long get_t0();
    bool operator< (Event* b) {
        return t0 < b->get_t0();
    }
    bool operator> (Event* b) {
        return t0 > b->get_t0();
    }
    
    void do_func(unsigned long t);

private:
    unsigned long t0, tT;   // begin and end time

    // next and previous event in list:
    Event* next;
    Event* prev;
    int append(Event* new_event);
    int prepend(Event* new_event);
    
    // event 
    const char** event_argv;
    unsigned long event_argc;


};

#endif
