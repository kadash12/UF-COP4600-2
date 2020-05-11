#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>

#include "./harness.h"

int* retrieve_set_tag_params(int pid, int new_tag) {
    int* arr = (int*)malloc(4 * sizeof(int));
    arr[0] = 335;
    arr[1] = 2;
    arr[2] = pid;
    arr[3] = new_tag;
    return arr;
}

int* retrieve_get_tag_params(int pid) {
    int* arr = (int*)malloc(3 * sizeof(int));
    arr[0] = 336;
    arr[1] = 1;
    arr[2] = pid;
    return arr;
}

int interpret_set_tag_result(int ret_value) {
    return ret_value;
}

int interpret_get_tag_result(int ret_value) {
    return ret_value;
}
//*************************************************
//Declare harness functions for project 2: Process Scheduling

//Returns an int array of 2-4 values that can be used to make the set_level_alloc system call
int* retrieve_set_alloc_params(int level, int new_alloc){
	int* k = (int*)malloc(4 * sizeof(int));
	k[0] = 337;
	k[1] = 2;
	k[2] = level;
	k[3] = new_alloc;
	return k;
}

//Returns an int array of 2-4 values that can be used to make the get_level_alloc system call.
int* retrieve_get_alloc_params(int level){
	int* k = (int*)malloc(3 * sizeof(int));
	k[0] = 338;
	k[1] = 1;
	k[2] = level;
	return k;
}

//After making the system call, we will pass the syscall return value to this function call. It should return set
//_alloc’s interpretation of the system call completing with return value ret_value.
int interpret_set_alloc_result(int ret_value){
	return ret_value;
}

//After making the system call, we will pass the syscall return value to this function call. It should return get
//_alloc’s interpretation of the system call completing with return value ret_value.
int interpret_get_alloc_result(int ret_value){
	return ret_value;
}
