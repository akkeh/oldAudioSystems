#include <iostream>
#include <cstdlib>
#define DEBUG
#include "KRNS_Event.h"
#include "KRNS_Track.h"

int main() {

    Track testTrack;
    testTrack.load(); 
    Event* last = testTrack.new_Event(10);

    last->process();
    

/*
    Event* event = testTrack.new_Event(10);
    if(!event)
        return -1;
    std::cout << "test process\n";
    event->process();
*/
};
