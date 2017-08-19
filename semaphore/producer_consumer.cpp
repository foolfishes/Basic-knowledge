#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

struct buffer
{
  char data[20];
  int n;  //number of product in data
  int p; //index of producer
  int c; //index of consumer
  buffer():n(20),p(-1),c(-1){}
};

int bk = 1;
buffer mybuf;
sem_t mutex, prod, cons;  // three semaphore 

void* producer_thread(void* arg)
{
  char ch = 'A';
  while(bk)
  {
    sem_wait(&prod);    //can produce
    sem_wait(&mutex);  //mutex the buff
    mybuf.data[(++mybuf.p)%mybuf.n] = ch;
    sem_post(&mutex);
    sem_post(&cons);   //tell consumer there is new product
    printf("%lu produce: %c\n", pthread_self(), ch);
    if(ch>='Z')
      ch = 'A';
    else
      ch = ch + 1;

    sleep(1);   //relax
  }
  
  return NULL;
}


void* consumer_thread(void* arg)
{
  char ch;
  while(bk)
  {
    sem_wait(&cons);  //wait for product 
    sem_wait(&mutex);
    ch = mybuf.data[(++mybuf.c)%mybuf.n];
    sem_post(&mutex);
    sem_post(&prod);  //tell producer there is a new buff to produce
    printf("%lu consume: %c\n", pthread_self(), ch);

    sleep(2);  //digest

  }
  return NULL;
 
}


int main()
{
  pthread_t pidp[5];
  pthread_t pidc[5];
  sem_init(&mutex, 0, 1);
  sem_init(&cons, 0, 0);    //at the begin there is 0 product ot consume
  sem_init(&prod, 0, 20);   //at the begin there are 20 product to produce

  for(int i=0; i<3; i++)
    pthread_create(&pidp[i], NULL, producer_thread, NULL);

  for(int i=0; i<3; i++)
    pthread_create(&pidc[i], NULL, consumer_thread, NULL);


  sleep(10);
  bk = 0;   //after 60s, stop the will
  int x = 3;
  while(x)
  {
    sem_post(&prod);
    printf("prod----\n");
    x--;
  }
  x = 3;
  while(x)
  {
    printf("cons----\n");
    sem_post(&cons);
    x--;
  }


  for(int i=0; i<3; i++)
    pthread_join(pidp[i], NULL);

  for(int i=0; i<3; i++)
    pthread_join(pidc[i], NULL);

  sem_destroy(&mutex);
  sem_destroy(&cons);
  sem_destroy(&prod);

  printf("finished\n");

  return 0;
}



