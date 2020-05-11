/*
*
*	@aauthor: Shashank Ranjan
*	Jan 29, 2020
*	Program to fetch and print the pid of the current process
*/

#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	pid_t  my_pid = getpid();

	printf("My pid is: %d\n", my_pid);

	return 0;
}
