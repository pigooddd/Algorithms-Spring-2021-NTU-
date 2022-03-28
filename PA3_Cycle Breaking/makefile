# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
# -c option ask g++ to compile the source files, but do not link.
# -O2 option is for optimized version
OPTFLAGS = -O3

all	: bin/cb
	@echo -n ""

# optimized version
bin/cb	: main.o
			$(CC) $(OPTFLAGS) main.o -o bin/cb
main.o 	   	: src/main.cpp
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o  bin/*

