#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include "tags.c"
#include <errno.h>
 #include <sched.h>

extern int errno;

int main(void) {
 int i = get_alloc(-1);
  printf("Get: Invalid level %d\n",i);
printf("Errno %d\n", errno);

 i = set_alloc( 1, -10);
  printf("Set: Negative time %d\n",-10);
printf("Errno %d\n", errno);


 i = set_alloc( 5, 5);
  printf("Set: Invalid level %d\n",5);
 printf("Errno %i\n",errno);

i=set_alloc(3,0);
i=set_alloc(2,0);
i=set_alloc(1,0);
i=set_alloc(0,0);
 printf("Set: Invalid total time %i\n",i);
 printf("Errno %i\n",errno);

struct timespec *tp;
printf("Get the time interval %i/n", sched_latency_ns());


  return 0;
}
