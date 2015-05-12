#ifndef KRNS_EVNT_H_
#define KRNS_EVNT_H_

class Event {
public:
    int add(Event* new_event, int rev);
    unsigned long get_startt();

    bool operator< (Event* b) {
        return this->start_t < b->get_startt();
    }
    
    bool operator> (Event* b) {
        return this->start_t > b->get_startt();
    }

private:
    unsigned long start_t;
    unsigned long dur;   
    Event* prev;
    Event* next;
    
    // methods:
    int prepend(Event* new_event);
    int append(Event* new_event);
};

#endif
