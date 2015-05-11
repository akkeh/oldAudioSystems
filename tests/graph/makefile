#CC-compiler:
CC=g++
CFLAGS = -Wall
FLFLAGS = `fltk-config -cxxflags`
LFLAGS = -lfltk -lXext -lX11 

OBJ = screen.o

all: test

test: ${OBJ}
	${CC} -o $@ ${CFLAGS} ${LFLAGS} ${OBJ}

.cpp.p:
	${CC} -c $< ${CFlAGS} ${FLFLAGS}

clean:
	rm -rf *.o
