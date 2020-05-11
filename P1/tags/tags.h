//Header for the library functions.
#ifndef TAGS
#define TAGS

#include <stdint.h>

//Put syscall number here.
#define __x64_sys_get_tag 335
#define __x64_sys_set_tag 336

//Declare library functions.
/*
Invokes system call which attempts to change the tag of the process identified by pid to the new tag
value new_tag. Returns new_level on success, and-1 otherwise.
*/
int set_tag (int pid, int new_tag);

/*
Invokes system call which reads the tag of the process identified by pid. Returns the new tag value
on success, and -1 otherwise.
*/
int get_tag (int pid);

#endif
