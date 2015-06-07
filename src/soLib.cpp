#include "KRNS_Track.h"

#ifdef __cplusplus
extern "C" {
#endif

Track* create_obj() {
    return new Track();
};

void destroy_obj(Track* obj) {
    delete obj;
};

int funcCount = 2;
char* funcNames[2] = { "clip", "test" };

// func1:
int clipArgc = 2;
char* clipArgn[2] = { "low", "high" };
void* clip( int argc, void** argv) {
    std::cout << "so lib says hi!\n";
    int* result;
/*    
    static int low = 0;
    static int hi = 0;
    low = *(int*)argv[1];
    hi = *(int*)argv[2];
    //result = (int*) statev[0];
    *result = low;
    if(*result < low) 
        *result = low;
    if(*result > hi) 
        *result = hi;
*/
    *result = 5;
    return (void*)  result;
};

// func2:
int testArgc = 0;
char* testArgn[0];
void* test(int argc, void** argv) {
    std::cout << "so Lib says hi!\n";
};


#ifdef __cplusplus
}
#endif


