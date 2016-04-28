#include <iostream>
#include <cstdlib>
#define DEBUG
#include "KRNS_Event.h"
#include "KRNS_Track.h"

void* func(int argc, void** argv) {
    if(argc < 1) return NULL;
    return argv[0];
};

int main() {
    int arg1 = 0;
    void** argv;
    argv = new void*[1];
    argv[0] = (void*) &arg1;

    Track testTrack;
    testTrack.load(); 
    Event* event = testTrack.new_Event(10);
    if(!event)
        return -1;
    std::cout << "test process\n";
    event->process();
};
