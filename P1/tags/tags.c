//Headers
#include "tags.h"

/*
Invokes system call which reads the tag of the process identified by pid. Returns the access level
on success, and -1 otherwise.
*/
int get_tag (int pid){
	uint32_t tag = syscall(__x64_sys_get_tag, pid);
        return tag;
}


/*
Invokes system call which attempts to change the tag of the process identified by pid to the new tag value
new_tag. Returns new_level on success, and -1 otherwise.
*/
int set_tag (int pid, int new_tag){
	uint32_t tag = syscall(__x64_sys_set_tag, pid, new_tag);
	return tag;
}

//Header
#include "harness.h"

//Returns an int array of 2-4 values that can be used to make the set-tag system call.
int* retrieve_set_tag_params(int pid,int new_tag){
        //int array of 4 values
        int *k = malloc(4);
        k[0]=336;       //System call number
        k[1]=2;         //2 Param
        k[2]=pid;       //Param: PID
        k[3]=new_tag;   //Param: tag
        return k;
}

//Returns an int array of 2-4 values that can be used to make the get-tag system call.
int* retrieve_get_tag_params(int pid){
        //int array of 3 values
        int *k = malloc(3);
        k[0]=335;       //System call number
        k[1]=1;         //1 Param
        k[2]=pid;       //Param: PID
        return k;
}

/*
After making the system call, we will pass the syscall return value to this function call.
It should return set_tag’s interpretation of the system call completing with return value
ret_value (i.e., what the library call should return to the user program).
*/
int interpret_set_tag_result(int ret_value){
        	return ret_value;
}

/*
After making the system call, we will pass the syscall return value to this function call.
It should return get_tag’s interpretation of the system call completing with return value
ret_value (i.e., what the library call should return to the user program).
*/
int interpret_get_tag_result(int ret_value){                                                                                    return ret_value;
                return ret_value;
}
