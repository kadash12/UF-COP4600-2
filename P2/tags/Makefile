#Johnny Li
#COP4600: OS
#3/1/2020
#P2: Makefile to compile library tags

#Macros
MAKE=make
CC = gcc
CFLAGS = -I.

#Make
default: clean libtags.a

tags.o: tags.c
	$(CC) -c tags.c $(CFLAGS)

harness.o: harness.c
	$(CC) -c harness.c $(CFLAGS)

libtags.a: tags.o harness.o
	ar cr libtags.a tags.o harness.o
	ranlib libtags.a

clean:
	rm -f *.a *.o *.h.gch

#Man pages
	sudo cp set_level_alloc.2.gz /usr/share/man/man2/set_level_alloc.2
	sudo cp get_level_alloc.2.gz /usr/share/man/man2/get_level_alloc.2
	sudo cp library.3.gz /usr/share/man/man3/set_alloc.3
	sudo cp library.3.gz /usr/share/man/man3/get_alloc.3
