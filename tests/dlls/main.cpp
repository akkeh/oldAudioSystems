#include "main.h"

#include <dlfcn.h>
#include <iostream>

int main() {
    std::cout << "opening lib\n";
    void* handle = dlopen("./test.so", RTLD_NOW);

    if(!handle) {
        std::cerr << "\nlib could not be opened!\n";
        return -1;
    }
    std::cout << "lib opened!\n";

    dlerror();  // reset errors
    f1 func = (f1) dlsym(handle, "func");
    const char* dlsym_err = dlerror();

    if(dlsym_err) {
        std::cerr << "function not found!\n";
        dlclose(handle);
        return -1;
    }
    
    int i = func(10);
    std::cout << "output: " << i << std::endl;

    std::cout << "function 2:\n";

    f2 proc = (f2) dlsym(handle, "proc");
    if(dlsym_err) {
        std::cerr << "func 2 not found!\n";
        return -1;
    }

    double y = proc(10.0);
    std::cout << "output: " << y << std::endl;


    dlclose(handle);
}
