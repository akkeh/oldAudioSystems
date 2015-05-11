#CC-compiler:
CC=g++

dlltest: main.cpp
	${CC} -o dlltest main.cpp -ldl
	export LD_LIBRARY_PATH=.


lib: test.cpp
	${CC} -shared -fPIC -o test.so test.cpp

clean:
	rm -rf *.o
