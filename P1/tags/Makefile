#Johnny Li
#COP4600: OS
#3/1/2020
#P1: Makefile to compile library tags

#Macros
CC=cc

#Make
tags.o: tags.c
	$(CC) -o tags.o -c tags.c
	ar cr libtags.a tags.o
#Man pages
	sudo cp set_tag.2.gz /usr/share/man/man2/set_tag.2
	sudo cp get_tag.2.gz /usr/share/man/man2/get_tag.2
	sudo cp library.3.gz /usr/share/man/man3/set_tag.3
	sudo cp library.3.gz /usr/share/man/man3/get_tag.3
	sudo cp harness.3.gz /usr/share/man/man3/retrieve_set_tag_params.3
	sudo cp harness.3.gz /usr/share/man/man3/retrieve_get_tag_params.3
	sudo cp harness.3.gz /usr/share/man/man3/interpret_get_tag_result.3
	sudo cp harness.3.gz /usr/share/man/man3/interpret_set_tag_result.3
