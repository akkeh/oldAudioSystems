#include "KRNS_Track.h"
#include <dlfcn.h>
#include <cstdlib>
#include <string>
#define DEBUG

void* Track::funcCall(int func_id, int argc, void** argv) {
    // get inputs
    
    return funcList[func_id](argc, argv);
};




int Track::load() {
    top:
    if(soLibName.empty()) {    // check if name is entered?
        std::cout << "Path to shared object file:\n\t$ ";
        std::cin >> soLibName;
    };

    //  open shared object:
    soHandle = dlopen(soLibName.c_str(), RTLD_NOW);
    if(!soHandle) { // opening not succesfull?
        std::cerr << "\nlib: " << soLibName << " could not be opened!\n";
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


    // load functions:
    // find function count:
    funcCount = *(int*) dlsym(soHandle, "funcCount");
    dlerr = dlerror();
    if(dlerr) {
        std::cerr << "\nerror reading function count: " << dlerr << "\n\n";
        dlclose(soHandle);
        return -1;
    }
    #ifdef DEBUG
        std::cout << "found: " << funcCount << " functions\n";
    #endif

    argcList = new int[funcCount];
    argnList = new char**[funcCount];
    funcNames = (char**) dlsym(soHandle, "funcNames");

    funcList = new func_t[funcCount];
    std::string funcArg;

    for(int i=0; i<funcCount; i++) {
        // load function:
        #ifdef DEBUG
            std::cout << "loading function: " << funcNames[i] << std::endl;
        #endif
        funcList[i] = (func_t) dlsym(soHandle, funcNames[i]);

        if(dlerr = dlerror()) {
            std::cerr << "\nerror loading " << funcNames[i] << ": " << dlerr << "\n\n"; 
        };

        // load argument list
        funcArg = std::string(funcNames[i]) + "Argc";        
        argcList[i] = *(int*) dlsym(soHandle, funcArg.c_str());
        if(dlerr = dlerror()) {
            std::cerr << "\nerror: " << dlerr << "\n\n";
        };
        #ifdef DEBUG
            std::cout << "\t" << funcNames[i] << " wants " << argcList[i] << " argument(s)\n";
        #endif

        funcArg = std::string(funcNames[i]) + "Argn";
        argnList[i] = (char**) dlsym(soHandle, funcArg.c_str());
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

Event* Track::new_Event(unsigned long t, int func_id, int argc, void** argv) {
    if(func_id == -1)
        chooseFunc(&func_id, &argc, argv);

    Event* new_Event = new Event(t, func_id, this, argc, argv);

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


void Track::chooseFunc(int* func_id, int* argc, void** argv) {
    // list functions:
    std::cout << "Available functions:\n";
        std::cout << "\tTrack functions:\n";
        int counter = 0;
        for(int i=0; i<funcCount; i++) {
            std::cout << "\t\t[" << i <<"]: " << funcNames[i] << std::endl;
            counter++;
        };
        std::cout << "\tEvent-related functions:\n";
        /*
        for(int i=0; i<Sced->funcCount; i++) {
            std::cout << "\t\t[" << i+counter << "]: " << Sced->funcNames[i] << std::endl;
            counter++;  
        };
        */
    std::cout << "/nSelect a function:\n\t$ ";
    std::cin >> *func_id;    
    if((*func_id < 0) || (*func_id > counter)) {
        std::cerr << "error: function not found!\n";
    };
    *argc = argcList[*func_id];
    argv = new void*[*argc];
    for(int i=0; i<*argc; i++) {
        std::cout << argnList[*func_id][i] << "\n\t$ ";
        std::cin >> argv[i];
    };
};


Track::Track() {
    funcNames = NULL;
    last = NULL;
};

Track::~Track() {
    // unload lib:
    if(soHandle)
        dlclose(soHandle);
};
