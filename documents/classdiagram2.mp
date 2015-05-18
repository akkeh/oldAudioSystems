input metauml

beginfig(1);
    Class.Sced("Scheduler")(
        "add_track(): int",
        "start(): int",
        "stop(): int"

    )(
        "+play(): int",
        "+play_t: unsigned long",   % playhead time
        "+eval_track(int): int",
         
        "+tracks: Track*",
        "+track_count: unsigned long",
         
        % graphic stuff:
        "+g_query_tracks(): void",
        "+(...)"
        % "+g_playhead(): void"
    );

    Class.Track_H("Track.h")(
        "typedef (*proc_t)(int, const char**): T",
        "typedef (*msg_t)(int, const char**): int",
        "typedef (*spawn_t)(int, const char**): int",
        "typedef (*kill_t)(int, const char**): int",
    )();

    Class.Track("<T>Track")(
        "add_event(unsigned long): void",
        "eval(unsgined long): void",
        "output(unsigned long): T",
    )(
        "+event_count: unsigned long",
        "+begin: Event*",
        "+end: Event*",
        "+last: Event*",    

        "+sofile: void*",
        "+proc: proc_t",
        "+msg: msg_t",
        "+spawn: spawn_t",
        "+kill: kill_t",

        "+mem_t: unsigned long",
        "+mem_outp[256]: T",
        "+mem_i: unsigned char",
        "+intern_t: unsgined char", % internal track time (i.e.: t of last call to eval())
                
        "+scheduler: Sced*",
        "+inputs: Track*",
        "inp_count: unsgined long",
        "tracks: Track*",
    
        % graphic stuff:
        "update_graph(): int"   % spawn/kill icons, msg icon & output waveform (+ t0 -> tT markings)
    );
 
    Class.Event("Event")(
        "add(Event*, int): void",
        "operator<(Event*): bool",
        "operator>(Event*): bool",
        "get_t0(): unsigned long",
        "do_func(unsigned long): void"  % send argc & argv to track; SEND EVENT TYPE? (proc, msg, spawn, kill)?
    )(
        "+next: Event*",
        "+prev: Event*",
        "+t0, tT: unsgined long",
        "+append(Event*): void",
        "+prepend(Event*): void",
        "+event_argv: const char***",
        "+event_argc: unsigned long"  % unsigned long == tT-t0;
    );

    topToBottom(45)(Sced, Track_H, Track, Event);   
    drawObjects(Sced, Track_H, Track, Event);
endfig;
end
