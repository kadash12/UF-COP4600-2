#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include "./tags.h"

extern int errno;

int set_tag(int pid, int new_tag) {
    return syscall(335, pid, new_tag);
}

int get_tag(int pid) {
    return syscall(336, pid);
}
//*************************************************
//Declare library functions for project 2: Process Scheduling

//Invokes system call which attempts to change the allocation of the level identified by level to the new allocation
//value new_allocation in milliseconds. Returns new_allocationon success, and -1 otherwise with errno set to an unused
//value you will document to explain the failure.
int set_alloc(int level, int new_allocation){
	errno=0;	//Reset errno

	//Check if valid arguments inputs
	if(!(level==0 || level==1 || level ==2 || level==3)){
		errno = EINVAL;
		return -1;
	}

	//Check if time is greater than or equal to 0
	if(new_allocation<0){
		errno = EPERM;  //Not greater than or equal to 0
		return -1;
	}

	//Temp storage
	int temp0=syscall(337, 0);
	int temp1=syscall(337, 1);
	int temp2=syscall(337, 2);
	int temp3=syscall(337, 3);

	int sys=syscall(338, level, new_allocation);

	//Set errno
	if(sys==-1){
		//Return -1 if not superuser
		errno = EACCES;
		return -1;
	}

	//Check amount of time
	int total = syscall(337, 0)+syscall(337, 1)+syscall(337, 2)+syscall(337, 3);
	if(total < 5){
		errno = 132;    //Total amount of time is less than 5ms
		//Reset values to original
		int temp = syscall(338, 0, temp0);
		temp = syscall(338, 1, temp1);
		temp = syscall(338, 2, temp2);
		temp = syscall(338, 3, temp3);

		return -1;
	}

	return sys;
}

//Invokes system call which reads the allocation of the level identified by level. Returns the allocation in
//milliseconds for that level on success, and -1 otherwise, with errno set to an unused value you will
//document to explain the failure.
int get_alloc(int level){
	errno =0;   //Reset errno
	int sys = syscall(337, level);

	//Set errno
	if(sys==-1){
		errno = EINVAL;	//Invalid argument
	}

	return sys;
}
