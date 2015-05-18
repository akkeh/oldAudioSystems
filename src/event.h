#ifndef KRNS_EVNT_H_
#define KRNS_EVNT_H_

class subEvent;

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

    Event(int argc, const char** argv, unsigned long t0, unsigned long tT);
    ~Event();
private:
    unsigned long t0, tT;   // begin and end time

    // next and previous event in list:
    Event* next;
    Event* prev;
    int append(Event* new_event);
    int prepend(Event* new_event);
    
    // event 
    const char** argv; 
    unsigned long argc;

    // sub-eventlist:
    unsigned long subEventc;
    Event* subEvents;
};

class subEvent : private Event {
public:
    subEvent(int argc, const char** argv, unsigned long t0);
    ~subEvent();

private:
    
};
#endif
