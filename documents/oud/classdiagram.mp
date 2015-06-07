input metauml

beginfig(1);
    Class.Track("Track<Type>")(
        "+sofile: void*", % so file handler
        "+process(unsigned long t): Type"
        "+Inputs: Track*",
        "+eventlist: Event*",
        "+last_t: unsigned long",
        "last_out: Type"
    )(   
        "output(unsigned long t): Type",
        "add_event(): void",
        "msg(): void",
        "spawn(): void"
    );
    
    drawObjects(Track);
endfig;
end
