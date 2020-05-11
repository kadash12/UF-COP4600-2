//Header for harness library.
#ifndef HARNESS
#define HARNESS

//Declare the harness functions.
//Returns an int array of 2-4 values that can be used to make the set-tag system call.
int* retrieve_set_tag_params(int pid,int new_tag);

//Returns an int array of 2-4 values that can be used to make the get-tag system call.
int* retrieve_get_tag_params(int pid);

/*
After making the system call, we will pass the syscall return value to this function call.
It should return set_tag’s interpretation of the system call completing with return value
ret_value (i.e., what the library call should return to the user program).
*/
int interpret_set_tag_result(int ret_value);

/*
After making the system call, we will pass the syscall return value to this function call.
It should return get_tag’s interpretation ofthe system call completing with return value
ret_value (i.e., what the library call should return to the user program).
*/
int interpret_get_tag_result(int ret_value);

#endif
