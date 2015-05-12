#ifndef KRNS_EVNT_H_
#define KRNS_EVNT_H_

class Event {
public:
    int add(Event* new_event, int rev);
    int append(Event* new_event);
    int prepend(Event* new_event);

private:
    Event* prev;
    Event* next;

};

#endif
