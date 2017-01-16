#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <pthread.h>
#include "defines.h"
// #include "jobQueue.h"

// typedef struct {
//    nodeIndex* in;
//    index*out;
// }threadParams;

class JobScheduler {
private:
   int numberOfThreads;
   pthread_t* workers;
   pthread_t worker;
   // jobQueue* jobs;

public:
   JobScheduler( int execution_threads);
   ~JobScheduler();
   pthread_t getWorkers(int);
   // void submit_job(job j);
   void submit_job(int j);
   void execute_all_jobs();
   void wait_all_tasks_finish(); //waits all submitted tasks to finish
   OK_SUCCESS destroy_scheduler();
};

#endif