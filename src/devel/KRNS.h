#ifndef KRNS_H_
#define KRNS_H_

#include <iostream>
// classes:
class Event;
class Track;
// -------

typedef Event* (*Event_constr)(unsigned long t, Track* track, int argc, void** argv);   // function typedef
typedef void (*Event_destr)(Event* event);
#include "KRNS_Track.h"
#include "KRNS_Event.h"
enum clock_types { OFFLINE, REALTIME };

class Time_t {
public:
    Time_t() :t(0) {};
    virtual unsigned long get_time() = 0;
protected:
    unsigned long t;
};

class Time_OFFLINE : public Time_t {
public:
    Time_OFFLINE() {};
    unsigned long get_time() {
        std::cout<< t << std::endl;
        return t++;
    };
};

class Clock_t {
private:
    Time_t* clockTime;
    unsigned long t0;  // start time
public:
    Clock_t(int type, unsigned long t_t0) : t0(t_t0), t(0){
        switch(type) {
            case 0:
                clockTime = new Time_OFFLINE();
                break;
            case 1:
                // clockTime = new Time_REALTIME();
                break;
            default:
                clockTime = new Time_OFFLINE();
                break;
        };
    };
    unsigned long get_time() {
        return clockTime->get_time() + t0;
    };
private:
    unsigned long long t;
};

#endif
