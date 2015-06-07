#ifndef KRNS_TRCK_H_
#define KRNS_TRCK_H_

#include <string>

#include "KRNS_Event.h"


class Track {
public:
    Track();
    ~Track();
    void output(int argc, void** argv, int outc, void** outv);

    Event* new_Event(unsigned long t, int event_id = -1, int argc = 0, void** argv = NULL);
    void chooseEvent(int* event_id, int* argc, void** argv);

    // so lib stuff:
    int load();    // load libary
   

    //void* funcCall(int func_id, int argc, void** argv); 
private:
    // track stuff:
    int statec; // internal state
    void** statev;

    void* output_mem;

    // so lib stuff:
    void* soHandle;
    std::string soLibName;
    Event_constr* constrList;
    Event_destr* destrList;
    int eventCount;
    char** eventNames;
    int* argcList;
    char*** argnList;

    // events:
    Event* last;
};
#endif
