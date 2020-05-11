//Johnny Li
//2/16/2020

//COP4600 - Operating Systems
//Spring 2020
//Exercise 5 
//Illustrating race conditions 

//Make command
//new_race: new_race.o
//	cc -o new_race new_race.o
//
//new_race.o: new_race.c
//	cc -c new_race.c

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define DEFAULT_IT 10000
int iterations = DEFAULT_IT;
int my_tid = 0;
int value = 0;

//Reference: https://stackoverflow.com/questions/9613934/pthread-race-condition-suspicious-behaviour
//Add mutex lock to prevent race conditions
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* loadSubRoutine( void* arg ) 
{
   int i = 0;
   for (i = 0; i < iterations; ++i) 
   {
	pthread_mutex_lock(&mutex);	//Mutex lock

	int tmp = value;
	++tmp;
	value = tmp;
   	printf("%d\n", value);

	pthread_mutex_unlock(&mutex);	//Mutex unlock
   }
}

int main(int argc, char* argv[])
{
   pthread_t l1, l2, l3, l4, l5; 

   if (argc > 1) 
   {
	int rv;
	rv = sscanf(argv[1], "%d", &iterations);
	if (rv != 1) 
	{
	   printf ("Bad rv=%d; argument=%s resulted in iterations=%d\n", 
		rv, argv[1], iterations);
	   return(1);
	}
   }

// create and run four threads 
   pthread_create(&l1, NULL, loadSubRoutine, NULL);
   pthread_create(&l2, NULL, loadSubRoutine, NULL);
   pthread_create(&l3, NULL, loadSubRoutine, NULL);
   pthread_create(&l4, NULL, loadSubRoutine, NULL);
   pthread_create(&l5, NULL, loadSubRoutine, NULL);

// wait for each to terminate
   pthread_join(l1, NULL);
   pthread_join(l2, NULL);
   pthread_join(l3, NULL);
   pthread_join(l4, NULL);
   pthread_join(l5, NULL);

// when all are dead, terminate
   printf("\n");
   return 0;
}

