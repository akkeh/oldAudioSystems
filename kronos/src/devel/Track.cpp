#include "KRNS_Track.h"
#include <dlfcn.h>
#include <cstdlib>
#include <string>
#define DEBUG

int Track::load() {
    top:
    if(soLibName.empty()) {    // check if name is entered?
        std::cout << "Path to shared object file:\n\t$ ";
        std::cin >> soLibName;
    };

    //  open shared object:
    soHandle = dlopen(soLibName.c_str(), RTLD_NOW);
    if(!soHandle) { // opening not succesfull?
        std::cerr << "\nlib: " << soLibName << " could not be opened:\n\t" << dlerror() << std::endl;
        
        soLibName.clear();
        goto top;   // try again;
    } else {
        #ifdef DEBUG
            std::cout << "lib: " << soLibName << " succesfully opened!\n";
        #endif
    }
    // initialise error system:
    dlerror();  // flush errors
    const char* dlerr;


    // load event-classes
    // find function count:
    eventCount = *(int*) dlsym(soHandle, "eventCount");
    dlerr = dlerror();
    if(dlerr) {
        std::cerr << "\nerror reading event count: " << dlerr << "\n\n";
        dlclose(soHandle);
        return -1;
    }
    #ifdef DEBUG
        std::cout << "found: " << eventCount << " events\n";
    #endif

    argcList = new int[eventCount];
    argnList = new char**[eventCount];
    eventNames = (char**) dlsym(soHandle, "eventNames");


    constrList = new Event_constr[eventCount];
    destrList = new Event_destr[eventCount];
    std::string eventArg;

    std::string constrName, destrName;
    for(int i=0; i<eventCount; i++) {
        // load function:
        #ifdef DEBUG
            std::cout << "loading function: " << eventNames[i] << std::endl;
        #endif
        constrName = "constr_" + std::string(eventNames[i]);
        destrName = "destr_" + std::string(eventNames[i]);
        constrList[i] = (Event_constr) dlsym(soHandle, constrName.c_str());
        destrList[i] = (Event_destr) dlsym(soHandle, destrName.c_str());
        if(dlerr = dlerror()) {
            std::cerr << "\nerror loading " << eventNames[i] << ": " << dlerr << "\n\n"; 
        };
        #ifdef DEBUG
            std::cout << "loading arguments\n";
        #endif
        // load argument list
        eventArg = std::string(eventNames[i]) + "Argc";        
        argcList[i] = *(int*) dlsym(soHandle, eventArg.c_str());
        if(dlerr = dlerror()) {
            std::cerr << "\nerror: " << dlerr << "\n\n";
        };
        #ifdef DEBUG
            std::cout << "\t" << eventNames[i] << " wants " << argcList[i] << " argument(s)\n";
        #endif

        eventArg = std::string(eventNames[i]) + "Argn";
        argnList[i] = (char**) dlsym(soHandle, eventArg.c_str());
        if(dlerr = dlerror()) {
            std::cerr << "\error: " << dlerr << "\n\n";
        };
        #ifdef DEBUG
            for(int j=0; j<argcList[i]; j++)
                std::cout << "\targument " << j << ": " << argnList[i][j] << std::endl;
        #endif

    };
    // process = (func_t) dlsym(soHandle, "process");    
};

Event* Track::new_Event(unsigned long t, int event_id, int argc, void** argv) {
    if(event_id == -1)
        chooseEvent(&event_id, &argc, &argv);
    Event* new_Event = constrList[event_id](t, this, argc, argv);

    std::cout << "Event made\n";
    if(!last) {
        last = new_Event;
        return new_Event;
    };
    if(last->add_Event(new_Event, 0) == 0) {
        last = new_Event;
        return new_Event;
    };
    return NULL;
};


int Track::chooseEvent(int* event_id, int* argc, void*** argv) {
    // list functions:
    std::cout << "Available events:\n";
        std::cout << "\tTrack events:\n";
        int counter = 0;
        for(int i=0; i<eventCount; i++) {
            std::cout << "\t\t[" << i <<"]: " << eventNames[i] << std::endl;
            counter++;
        };
        /*
        for(int i=0; i<Sced->funcCount; i++) {
            std::cout << "\t\t[" << i+counter << "]: " << Sced->funcNames[i] << std::endl;
            counter++;  
        };
        */
    std::cout << "\nSelect an event:\n\t$ ";
    std::cin >> *event_id;    
    if((*event_id < 0) || (*event_id >= counter)) {
        std::cerr << "error: event not found!\n";
        return -1;
    };
    *argc = argcList[*event_id];
    std::cout << "argc: " << *argc << std::endl;
    *argv = new void*[*argc];
    for(int i=0; i<*argc; i++) {
        std::cout << argnList[*event_id][i] << "\n\t$ ";
        int* arg = new int;
        std::cin >> *arg;
        *argv[i] = (void*)arg;
    };
    return 0;
};


Track::Track() {
    eventNames = NULL;
    last = NULL;
};

Track::~Track() {
    // unload lib:
    if(soHandle)
        dlclose(soHandle);
};
