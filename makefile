#CC-compiler:
CC=g++
CFLAGS = -Wall

DIR=outp

OBJ = main.o wavio.o fft.o #simpleproc.o #amps.o ztrans.o dft.o convolve.o fft.o

all: test

test: ${OBJ}
	${CC} -o $@ ${CFLAGS} ${OBJ}

.cpp.p:
	${CC} -c $< ${CFlAGS}

clean:
	rm -rf *.o
