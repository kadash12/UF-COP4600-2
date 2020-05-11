//Exercise 4 
//Spring 2020
//COP4600 - Operating Systems
//Dr. Jeremiah Blanchard, Vitaliy Kurishko, Dr. R. Newman
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
//Process struct
typedef struct process {
   int data;   
   int pid;
}process;
sem_t semaphore;
struct process* processTable[10];
//struct process* entry;
//Inserts process into table
void insert(int index, process* entry){
   if(processTable[index] == NULL){
      processTable[index] = entry;
   }
   else{
      printf("REQUEST TO TABLE DENIED!\n");
   } 
}
//Deletes process from table
void delete(int index){
   if(processTable[index] != NULL){
      processTable[index] = NULL;
   }
   else{
      printf("PROCESS MAY NOT BE STOPPED\n");
   }
}
void print(){
   printf(" -PID- -DATA- ");
   printf("\n");
   for(int i = 0; i < 10; ++i){
      if(processTable[i] != NULL){
         printf("[ %d ][ %d ]", processTable[i]->pid, processTable[i]->data);
         printf("\n");
      }
      else{
         printf("[ --- ][ -- ]");
         printf("\n");
      }
   }
}
//Process load routine
void* loadSubRoutine(void* arg){
   //Queue semaphore wait
   sem_wait(&semaphore);
   //Manually Instantiate Processees//
   //-------CRITICAL SECTION--------//
   process* process1 = (struct process*) malloc(sizeof(struct process));
   process* process2 = (struct process*) malloc(sizeof(struct process));
   process* process3 = (struct process*) malloc(sizeof(struct process));
   process* process4 = (struct process*) malloc(sizeof(struct process));
   process1->data = 35;
   process1->pid = 111;
   sleep(2);
   process2->data = 30;
   process2->pid = 256;
   sleep(2);
   process3->data = 44;
   process3->pid = 360;
   sleep(2);
   process4->data = 37;
   process4->pid = 420;
   //---------------------//
   //Loads processes into process table
   insert(0, process1);
   insert(1, process2);
   insert(3, process3);
   insert(2, process4);
   
   //A seg fault there was a failure to initialize a pointer before accessing it.
   //Cannot to write to arbitrary memory locations.
   //This was fixed by initializing the pointer and then utilizing it in memset().
   char* cp = 0x100;	//Initialize a char pointer at 0x100.                                                                           
   memset(&cp, 1, 100);	//Utilizing cp.

   //Prints table
   print();
   //Release semaphore
   sem_post(&semaphore);
}
int main(){
   //Event triggered by I/O
   //Instantiates semaphore for task priority
   srand(getpid());
   sem_init(&semaphore, 0 , 1);
   pthread_t l1; 
   pthread_create(&l1, NULL, loadSubRoutine, NULL);
   sleep(4);
   pthread_join(l1, NULL);
   sem_destroy(&semaphore);
   return 0;
}

