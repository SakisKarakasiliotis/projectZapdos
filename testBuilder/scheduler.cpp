#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/syscall.h>
#include "scheduler.h"
#include <unistd.h>

unsigned int microseconds=200000;


#include "job.h"

// void threadFun();


   static pthread_mutex_t queueLock;
   static pthread_mutex_t actualQueueLock;
   pthread_cond_t cond;
   
   

JobScheduler::JobScheduler( int execution_threads) {
   std::cout<<"POYTSES"<<std::endl;
   pthread_mutex_init ( &queueLock, NULL);
   pthread_mutex_init ( &actualQueueLock, NULL);   
   this->numberOfThreads = execution_threads;
   this->workers = (pthread_t*) malloc(execution_threads * sizeof(pthread_t));
   pthread_cond_init(&cond, NULL);
   this->jobs = new jobQueue(10000);
  
   std::cout<<"POYTSES 22"<<std::endl;
   for (int i = 0; i < 10000; ++i)
   {
      staticJob* j = new staticJob(i, 0, 0);
      this->jobs->enqueue(j);
   }
   for (int i=0; i<execution_threads; i++) {
      std::cout<<"POYTSES 33"<<std::endl;
      threadParams* params= new threadParams;
      params->threadno = i;
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
   // OK_SUCCESS err;
   bool flag = true;
   pthread_mutex_lock(&queueLock);
   // pid_t x = syscall(__NR_gettid);
   while (flag){
      // std::cout << 
       pthread_cond_wait(&cond, &queueLock);
       while(!k->array_of_jobs->isEmpty()){
         pthread_mutex_lock(&actualQueueLock);
         job* j = k->array_of_jobs->dequeue();
         pthread_mutex_unlock(&actualQueueLock);
         if (j != NULL) {
            printf(" %d\n", k->threadno);
            j->executeQuery();
         }
         // usleep(microseconds);
         pthread_mutex_unlock(&queueLock);
       }
       flag = false;      
   }
   // pthread_mutex_unlock(&queueLock);
   printf("%d exiting.\n",k->threadno);
   pthread_exit(NULL);
   return NULL;
}

// void JobScheduler::submit_job(job j){
   void JobScheduler::submit_job(int j){
   // this->jobs->enqueue(j);
}

void JobScheduler::execute_all_jobs(){
   pthread_mutex_unlock(&queueLock);
}

pthread_t JobScheduler::getWorkers(int i){
   return workers[i];
} //waits all submitted tasks to finish

int main(int argc, char const *argv[])
{
   int x;
   int numOfWorkers = 4;
   JobScheduler* s = new JobScheduler(numOfWorkers);
   // std::cin>>x;
   usleep(microseconds);
   pthread_cond_broadcast( &cond );
   for (int j=0; j<numOfWorkers; j++) {
      pthread_join(s->getWorkers(j), NULL);
   }

   return 0;
}