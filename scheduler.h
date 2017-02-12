#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <pthread.h>
#include "defines.h"
//#include "Q.h"
#include "jobQueue.h"
#include "bfs.h"
#include "job.h"


typedef struct {
   // nodeIndex* in;
   // index*out;
   int threadno;
   int numberOfThreads;
   jobQueue* array_of_jobs;
}threadParams;

class JobScheduler {
private:
   int numberOfThreads;
   pthread_t* workers;
   pthread_t worker;
   jobQueue* jobs;
   int numOfJobs;


public:
   JobScheduler( int execution_threads);
   ~JobScheduler();
   bool printQueue();
   pthread_t getWorkers(int);
   // void submit_job(job j);
   bool submit_job(job* j);
   void execute_all_jobs();
   void wait_all_tasks_finish(); //waits all submitted tasks to finish
   OK_SUCCESS destroy_scheduler();
   static  void *threadFun(void *);
};

#endif