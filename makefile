#CC-compiler:
CC=g++
CFLAGS = -Wall -ldl


OBJ = main.o track.o event.o

all: test

test: ${OBJ}
	${CC} -o $@ ${CFLAGS} ${OBJ}

.cpp.p:
	${CC} -c $< ${CFlAGS}


lib: test.cpp
	${CC} -shared -fPIC -o test.so test.cpp
clean:
	rm -rf *.o
