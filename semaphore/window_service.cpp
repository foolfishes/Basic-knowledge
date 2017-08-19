#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//function for thread to run
sem_t sem;  //global semaphore 

void* thread_fun(void* ids)
{
  char* id = (char*)(ids);
  if(sem_wait(&sem)==0)
  {
    sleep(3);
    printf("service: %c 3 seconds\n", *id);
    sem_post(&sem); //servive finished, next one can get the service 
  }
  return NULL;

}


int main()
{
  const int NUM = 10;   //10 people need service
  pthread_t pid[NUM];
  char name[NUM] = {'a','b','c','d','e','f','g','h','i','j'};

  sem_init(&sem,0,3); // three people can get servive at same time

  for(int i=0; i<NUM; i++)
  {
    pthread_create(&pid[i], NULL, thread_fun, &name[i]);
  }

  for(int i=0; i<NUM; i++)
    pthread_join(pid[i],NULL);

  printf("finished\n");

  sem_destroy(&sem);

  return 0;
}
