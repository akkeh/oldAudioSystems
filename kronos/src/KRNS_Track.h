#ifndef KRNS_TRCK_H_
#define KRNS_TRCK_H_

#include <string>

#include "KRNS_Event.h"


class Track {
public:
    Track();
    ~Track();
    void output(int argc, void** argv, int outc, void** outv);

    Event* new_Event(unsigned long t, int func_id = -1, int argc = 0, void** argv = NULL);
    void chooseFunc(int* func_id, int* argc, void** argv);

    // so lib stuff:
    int load();    // load libary
   

    void* funcCall(int func_id, int argc, void** argv); 
private:
    // track stuff:
    int statec; // internal state
    void** statev;

    void* output_mem;

    // so lib stuff:
    void* soHandle;
    std::string soLibName;
    func_t* funcList;
    int funcCount;
    char** funcNames;
    int* argcList;
    char*** argnList;

    // events:
    Event* last;
};

/*
// arguments:
class Arg {
private:
    int intArgc;
    int* intArgv;
    int* int_swp;

    char** argNames;
    char** names_swp;

public:
    void add_arg(char* argName, int val) {
        static bool newArg = true;
        static int index = 0;
        for(int i=0; i<intArgc; i++)
            if(argNames[i] == argName) {
                newArg = false;
                index = i;
            };
        if(newArg) {
            add_int(val);
            add_name(argName);
        } else {
            set_arg(index, val);
        }
    };

    void set_arg(int index, int val) {
        intArgv[index] = val;
    };

    int get_arg(int index) {
        if((index < 0) || (index > intArgc))
            return -1;
        return get_int(index);
    };

private:
    void add_int(int val) {
        int_swp = new int[intArgc + 1];
        for(int i=0; i<intArgc; i++)
            int_swp[i] = intArgv[i];
        int_swp[intArgc] = val;
        
        if(intArgv)
            delete intArgv;
        intArgv = int_swp;

        intArgc++;
    };

    void add_name(char* argName) {
        names_swp = new char*[intArgc];
        for(int i=0; i<intArgc-1; i++) 
            names_swp[i] = argNames[i];
        names_swp[intArgc-1] = argName;
        
        if(argNames)
            delete argNames;
        argNames = names_swp;
    };

    int get_int(int index) {
        return intArgv[index];
    };
};
*/
#endif
