#include "KRNS_Event.h"
#include "KRNS_Track.h"
#include "KRNS.h"

#ifdef __cplusplus
extern "C" {
#endif

int eventCount = 1;
char* eventNames[1] = { "testEvent" };

class testEvent : public Event {
public:
    testEvent(unsigned long t_t, Track* t_track, int t_argc = 0, void** t_argv = NULL, bool isTemp = false);
    void process();
    
private:
    int x;
};

int testEventArgc = 1;
char* testEventArgn[1] = { "test: int" };

testEvent* constr_testEvent(unsigned long t_t, Track* t_track, int t_argc, void** t_argv, bool isTemp) {
    return new testEvent(t_t, t_track, t_argc, t_argv, isTemp);
};

void destr_testEvent(testEvent* obj) {
    delete obj;
}; 


#ifdef __cplusplus
}
#endif

testEvent::testEvent(unsigned long t_t, Track* t_track, int t_argc, void** t_argv, bool t_isTemp)
    : Event(t_t, t_track, t_argc, t_argv, t_isTemp) {
    x = 10;
}; 

void testEvent::process() {
    std::cout << "so lib says hi!\n x = " << x << "\n argc: " << argc << std::endl;
    if(argv) {
        std::cout << "argv[0]: " << *(int*)argv[0] << std::endl;
    }; 
};

