#ifndef KRNS_LLIB
#define KRNS_LLIB

class TrackLib {
    typedef void* (*proc_t)(int argc, const char** argv);
    typedef int (*msg_t)(int argc, const char** argv);
    typedef int (*spawn_t)(int argc, const char** argv);
    typedef int (*kill_t)(int argc, const char** argv);
    proc_t proc;
    msg_t msg;
    spawn_t spawn;
    kill_t kill;



};




#endif
