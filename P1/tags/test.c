#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h> 

int main() 
{ 
  sleep(30);
    // make two process which run same 
    // program after this instruction 
 while(1){
    fork(); 

 printf("my process ID is %d\n", getpid());  

sleep(10);

}
    return 0; 
}
