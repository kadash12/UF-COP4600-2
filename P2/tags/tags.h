#ifndef TAGS_H
#define TAGS_H

int set_tag(int pid, int new_tag);

int get_tag(int pid);
//*************************************************
//Declare library functions for project 2: Process Scheduling

//Invokes system call which attempts to change the allocation of the level identified by level to the new allocation
//value new_allocation in milliseconds. Returns new_allocationon success, and -1 otherwise with errno set to an unused
//value you will document to explain the failure.
int set_alloc(int level, int new_allocation);

//Invokes system call which reads the allocation of the level identified by level. Returns the allocation in
//milliseconds for that level on success, and -1 otherwise, with errno set to an unused value you will
//document to explain the failure.
int get_alloc(int level);
#endif
