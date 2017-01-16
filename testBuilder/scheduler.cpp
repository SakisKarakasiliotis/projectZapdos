#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/syscall.h>
#include "scheduler.h"
#include <unistd.h>

unsigned int microseconds=200000;


// #include "job.h"

// void threadFun();
void *threadFun(void *);

   static pthread_mutex_t queueLock;
   pthread_cond_t cond;
   
   int* jobs;

JobScheduler::JobScheduler( int execution_threads) {
   std::cout<<"POYTSES"<<std::endl;
   pthread_mutex_init ( &queueLock, NULL);
   this->numberOfThreads = execution_threads;
   this->workers = (pthread_t*) malloc(execution_threads * sizeof(pthread_t));
   pthread_cond_init(&cond, NULL);
   // this->jobs = new jobQueue(50);
   jobs = new int[50]; 
   std::cout<<"POYTSES 22"<<std::endl;
   for (int i = 0; i < 50; ++i)
   {
      jobs[i] = i;
   }
   for (int i=0; i<execution_threads; i++) {
            std::cout<<"POYTSES 33"<<std::endl;

      pthread_create(&*(workers+i), NULL, &threadFun,  &i);
            std::cout<<"POYTSES 4"<<std::endl;

   }
}

JobScheduler::~JobScheduler(){
   // delete this->jobs;
}

int i=0;

void* threadFun(void* params) {
   int k = *((int*) params);
   // pthread_mutex_lock(&queueLock);
   bool flag = true;
   // pid_t x = syscall(__NR_gettid);
   while (flag){
       pthread_cond_wait(&cond, &queueLock);
       while(i<50){
         std::cout<<jobs[i]<<" " << pthread_self() << " " << k <<std::endl;
         usleep(microseconds);
         i++;
       }
       flag = false;      
   }
   pthread_mutex_unlock(&queueLock);
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
   int numOfWorkers = 2;
   JobScheduler* s = new JobScheduler(numOfWorkers);
   std::cin>>x;
   pthread_cond_broadcast( &cond );
   for (int j=0; j<numOfWorkers; j++) {
      pthread_join(s->getWorkers(j), NULL);
   }

   return 0;
}