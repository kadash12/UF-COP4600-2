#ifndef HARNESS_H
#define HARNESS_H

int* retrieve_set_tag_params(int pid, int new_tag);

int* retrieve_get_tag_params(int pid);

int interpret_set_tag_result(int ret_value);

int interpret_get_tag_result(int ret_value);
//*************************************************
//Declare harness functions for project 2: Process Scheduling

//Returns an int array of 2-4 values that can be used to make the set_level_alloc system call
int* retrieve_set_alloc_params(int level, int new_alloc);

//Returns an int array of 2-4 values that can be used to make the get_level_alloc system call.
int* retrieve_get_alloc_params(int level);

//After making the system call, we will pass the syscall return value to this function call. It should return set
//_alloc’s interpretation of the system call completing with return value ret_value.
int interpret_set_alloc_result(int ret_value);

//After making the system call, we will pass the syscall return value to this function call. It should return get
//_alloc’s interpretation of the system call completing with return value ret_value.
int interpret_get_alloc_result(int ret_value);
#endif
