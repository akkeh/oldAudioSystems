#CC-compiler:
CC=g++
CFLAGS = -Wall

DIR=outp

OBJ = zandb.o wavio.o amps.o simple_proc.o ztrans.o dft.o convolve.o fft.o

all: test

test: ${OBJ}
	${CC} -o $@ ${CFLAGS} ${OBJ}

.cpp.p:
	${CC} -c $< ${CFlAGS}

clean:
	rm -rf *.o
