MAKE = make
CC = gcc
CFLAGS = -L./tags -ltags -L. -lp1_test_util

default: clean p2_student_test

libtags: 
	cd tags && $(MAKE)

p2_student_test: p2_student_test.c util.c tests.c libtags libp1_test_util.a
	$(CC) -o p2_student_test p2_student_test.c util.c tests.c $(CFLAGS)

clean:
	rm -f *.o *.h.gch p2_student_test