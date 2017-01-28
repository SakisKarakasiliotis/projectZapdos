#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/syscall.h>
#include "scheduler.h"
#include <unistd.h>

unsigned int microseconds=200000;



// void threadFun();
static int remainingThreads;
static pthread_mutex_t remainingMux;
static pthread_mutex_t allThreadsReady;

static pthread_mutex_t condLock;
static pthread_mutex_t tasksLock;
static pthread_mutex_t queueLock;

pthread_cond_t cond;
pthread_cond_t tasksFinished;


JobScheduler::JobScheduler( int execution_threads) {
   std::cout<<"POYTSES"<<std::endl;
   pthread_mutex_init (&condLock, NULL);
   pthread_mutex_init (&tasksLock, NULL);
   pthread_mutex_init (&queueLock, NULL);
   pthread_mutex_init (&allThreadsReady, NULL);
   pthread_mutex_lock (&allThreadsReady);
   pthread_mutex_init (&remainingMux, NULL);
   this->numberOfThreads = execution_threads;
   remainingThreads = this->numberOfThreads;
   this->workers = (pthread_t*) malloc(execution_threads * sizeof(pthread_t));
   pthread_cond_init(&cond, NULL);
   pthread_cond_init(&tasksFinished, NULL);
   this->jobs = new jobQueue(JOB_Q_SIZE);

   std::cout<<"POYTSES 22"<<std::endl;
   for (int i=0; i<execution_threads; i++) {
      std::cout<<"POYTSES 33"<<std::endl;
      threadParams* params= new threadParams;
      params->threadno = i;
      params->numberOfThreads = this->numberOfThreads;
      params->array_of_jobs = this->jobs;
      pthread_create(&*(workers+i), NULL, &threadFun, (void*) params);
      std::cout<<"POYTSES 4"<<std::endl;

   }
}

JobScheduler::~JobScheduler(){
   // delete this->jobs;
}

int i=0;

void* JobScheduler::threadFun(void* params) {
   threadParams* k = (threadParams*) params;
   printf("No %d entered threadFun.\n", k->threadno);
   // OK_SUCCESS err;
   bool flag = true;
   pthread_mutex_lock(&condLock);
   printf("No %d passed mutex_lock.\n", k->threadno);
   // pid_t x = syscall(__NR_gettid);
   //------BARRIER TECHNIQUE-----
      pthread_mutex_lock(&remainingMux);
      remainingThreads--;
      pthread_mutex_unlock(&remainingMux);
   //---------------------------
   while (flag){
   //printf("No %d entered while.\n", k->threadno);
      if (remainingThreads==0) {
         pthread_mutex_unlock(&allThreadsReady);
      }
      pthread_cond_wait(&cond, &condLock);
      while(!k->array_of_jobs->isEmpty()){
         pthread_mutex_lock(&queueLock);
         job* j = k->array_of_jobs->dequeue();
         pthread_mutex_unlock(&queueLock);
         if (j != NULL) {
            printf(" %d\n", k->threadno);
            j->executeQuery();
         }
         // usleep(microseconds);
         pthread_mutex_unlock(&condLock);
      }
      //------BARRIER TECHNIQUE-----
      pthread_mutex_lock(&remainingMux);
      remainingThreads++;
      if (remainingThreads==k->numberOfThreads) {
         pthread_cond_broadcast(&tasksFinished);
      }
      pthread_mutex_unlock(&remainingMux);
   //---------------------------
      pthread_mutex_lock(&condLock);
   }
   // pthread_mutex_unlock(&condLock);
   printf("%d exiting.\n",k->threadno);
   pthread_exit(NULL);
   return NULL;
}

bool JobScheduler::submit_job(job* j){
   if(this->jobs->enqueue(j))
   return true;
   else return false;
}

void JobScheduler::execute_all_jobs(){
   pthread_mutex_lock(&allThreadsReady);
   cout << "Before broadcast"<<endl;
  // usleep(microseconds);
   pthread_cond_broadcast( &cond );
   cout << "After broadcast"<<endl;
   pthread_mutex_unlock(&allThreadsReady);
}

pthread_t JobScheduler::getWorkers(int i){
   return workers[i];
} //waits all submitted tasks to finish

void JobScheduler::wait_all_tasks_finish()
{
   pthread_mutex_lock(&tasksLock);
   pthread_cond_wait(&tasksFinished, &tasksLock);
   pthread_mutex_unlock(&tasksLock);
}

bool JobScheduler::printQueue(){
   return this->jobs->printQueue();
}