#CC-compiler:
CC=g++
CFLAGS = -Wall -ldl


OBJ = main.o Event.o Track.o
all: kronos

kronos: ${OBJ}
	${CC} -o $@ ${CFLAGS} ${OBJ}

.cpp.p:
	${CC} -c $< ${CFlAGS}


lib: soLib.cpp
	${CC} -shared -fPIC -o soLib.so soLib.cpp Event.cpp Track.cpp
clean:
	rm -rf *.o
