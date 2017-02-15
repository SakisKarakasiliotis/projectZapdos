#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/syscall.h>
#include "scheduler.h"
#include <unistd.h>


int i=0;
static int remainingThreads;
static int threadsFinished = 0;
static pthread_mutex_t remainingMux;
static pthread_mutex_t allThreadsReady;
static int* results;

static pthread_mutex_t condLock;
static pthread_mutex_t tasksLock;
static pthread_mutex_t queueLock;

pthread_cond_t cond;
pthread_cond_t tasksFinished;
pthread_cond_t threadsReady;


JobScheduler::JobScheduler( int execution_threads) {
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
   pthread_cond_init(&threadsReady, NULL);
   pthread_cond_init(&tasksFinished, NULL);
   this->jobs = new jobQueue(JOB_Q_SIZE);

   for (int i=0; i<execution_threads; i++) {
      threadParams* params= new threadParams;
      params->threadno = i;
      params->numberOfThreads = this->numberOfThreads;
      params->array_of_jobs = this->jobs;
      pthread_create(&*(workers+i), NULL, &threadFun, (void*) params);
   }
}

JobScheduler::~JobScheduler(){
}



void* JobScheduler::threadFun(void* params) {
   threadParams* threadParameters = (threadParams*) params;

   int bfs_result = 0;
   bool flag = true;


   while (flag){
       pthread_mutex_lock(&remainingMux);
       remainingThreads--;
       //---------------------------
       pthread_mutex_lock(&condLock);

       if (remainingThreads==0) {
           remainingThreads = THREAD_NUMBER;
           pthread_mutex_unlock(&allThreadsReady);
       }
       pthread_mutex_unlock(&remainingMux);
       pthread_cond_wait(&cond, &condLock);
       while(!threadParameters->array_of_jobs->isEmpty()){
             pthread_mutex_lock(&queueLock);
             job* j = threadParameters->array_of_jobs->dequeue();
             pthread_mutex_unlock(&queueLock);
             if (j != NULL) {
                bfs_result = j->executeQuery();
                int id = j->getID();
                 results[id]=bfs_result;
             }
       }

      pthread_mutex_unlock(&condLock);
      //------BARRIER TECHNIQUE-----
      pthread_mutex_lock(&remainingMux);
      threadsFinished++;
      if (threadsFinished==threadParameters->numberOfThreads) {
          threadsFinished = 0;
          pthread_mutex_unlock(&tasksLock);
          pthread_mutex_lock(&allThreadsReady);
      }
       pthread_mutex_unlock(&remainingMux);

       //---------------------------
   }
   pthread_exit(NULL);
   return NULL;
}

bool JobScheduler::submit_job(job* j){
   if(this->jobs->enqueue(j))
   return true;
   else return false;
}

void JobScheduler::execute_all_jobs(){
   this->numOfJobs = jobs->getNumberOfElements();
   results = new int[numOfJobs];
   pthread_mutex_lock(&allThreadsReady);
   pthread_mutex_lock(&tasksLock);
   pthread_cond_broadcast( &cond );
   pthread_mutex_unlock(&allThreadsReady);
}

pthread_t JobScheduler::getWorkers(int i){
   return workers[i];
}

void JobScheduler::wait_all_tasks_finish()
{
   pthread_mutex_lock(&tasksLock);
   pthread_mutex_unlock(&tasksLock);
   for (int j = 0; j < this->numOfJobs; j++) {
       cout<< results[j] << endl;
   }
   delete[] results;
}

bool JobScheduler::printQueue(){
   return this->jobs->printQueue();
}