#EX - 1 Make and libraries 
# --- macros
CC=cc

# --- targets
# --- makefile
useLib: useLib.o libmath.a
	$(CC) -o useLib useLib.o libmath.a -LI

main: main.o bar.o
	$(CC) -o main main.o bar.o
	
main.o: main.c
	$(CC) -c main.c
	
bar.o: bar.c bar.h
	$(CC) -c bar.c 

# --- Library
math_lib.o: math_lib.c mathlib.h
	$(CC) -c math_lib.c

libmath.a: math_lib.o
	ar cr libmath.a math_lib.o 
	ranlib libmath.a

useLib.o: useLib.c mathlib.h
	$(CC) -c useLib.c 
	
# --- remove binary and executable files
clean:
	rm main.o bar.o main
	rm useLib.o math_lib.o useLib
