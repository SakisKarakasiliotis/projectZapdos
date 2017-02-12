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
   pthread_cond_init(&threadsReady, NULL);
   pthread_cond_init(&tasksFinished, NULL);
   this->jobs = new jobQueue(JOB_Q_SIZE);

   for (int i=0; i<execution_threads; i++) {
      threadParams* params= new threadParams;
      params->threadno = i;
      params->numberOfThreads = this->numberOfThreads;
      params->array_of_jobs = this->jobs;
      //params->results = this->result_table;
      pthread_create(&*(workers+i), NULL, &threadFun, (void*) params);
   }
}

JobScheduler::~JobScheduler(){
   // delete this->jobs;
}

int i=0;

//void* JobScheduler::threadFun(void* params) {
//   threadParams* k = (threadParams*) params;
//   printf("No %d entered threadFun.\n", k->threadno);
//   // OK_SUCCESS err;
//   bool flag = true;
//   pthread_mutex_lock(&condLock);
//   printf("No %d passed mutex_lock.\n", k->threadno);
//   // pid_t x = syscall(__NR_gettid);
//   //------BARRIER TECHNIQUE-----
//      pthread_mutex_lock(&remainingMux);
//      remainingThreads--;
//      pthread_mutex_unlock(&remainingMux);
//   //---------------------------
//   while (flag){
//   //printf("No %d entered while.\n", k->threadno);
//      if (remainingThreads==0) {
//         pthread_mutex_unlock(&allThreadsReady);
//      }
//      pthread_cond_wait(&cond, &condLock);
//
//      while(!k->array_of_jobs->isEmpty()){
//         pthread_mutex_lock(&queueLock);
//         job* j = k->array_of_jobs->dequeue();
//         pthread_mutex_unlock(&queueLock);
//         if (j != NULL) {
//            printf(" %d\n", k->threadno);
//            j->executeQuery();
//         }
//         // usleep(microseconds);
//         pthread_mutex_unlock(&condLock);
//      }
//
//      //------BARRIER TECHNIQUE-----
//      pthread_mutex_lock(&remainingMux);
//      remainingThreads++;
//      if (remainingThreads==k->numberOfThreads) {
//         pthread_cond_broadcast(&tasksFinished);
//      }
//      pthread_mutex_unlock(&remainingMux);
//   //---------------------------
//      pthread_mutex_lock(&condLock);
//   }
//   // pthread_mutex_unlock(&condLock);
//   printf("%d exiting.\n",k->threadno);
//   pthread_exit(NULL);
//   return NULL;
//}
void* JobScheduler::threadFun(void* params) {
   threadParams* threadParameters = (threadParams*) params;
   printf("No %d entered threadFun.\n", threadParameters->threadno);
   // OK_SUCCESS err;

   int bfs_result = 0;
   bool flag = true;
   printf("No %d passed mutex_lock.\n", threadParameters->threadno);
   // pid_t x = syscall(__NR_gettid);


   while (flag){
       //------BARRIER TECHNIQUE-----
       pthread_mutex_lock(&remainingMux);
       remainingThreads--;
       //---------------------------
       pthread_mutex_lock(&condLock);

       if (remainingThreads==0) {
           cout<<"remaining threads 0"<<endl;
           remainingThreads = THREAD_NUMBER;
           pthread_mutex_unlock(&allThreadsReady);
//          pthread_cond_broadcast( &threadsReady );
       }
       pthread_mutex_unlock(&remainingMux);

       //while(threadParameters->array_of_jobs->isEmpty()) {
          pthread_cond_wait(&cond, &condLock);
     // }

      while(!threadParameters->array_of_jobs->isEmpty()){
         pthread_mutex_lock(&queueLock);
         job* j = threadParameters->array_of_jobs->dequeue();
         pthread_mutex_unlock(&queueLock);
         if (j != NULL) {
//            printf(" %d\n", threadParameters->threadno);
            bfs_result = j->executeQuery();
            int id = j->getID();
             cout <<"this is the job id :"<< id << endl;
             results[id]=bfs_result;
         }
      }

      pthread_mutex_unlock(&condLock);
      //------BARRIER TECHNIQUE-----
      pthread_mutex_lock(&remainingMux);
      threadsFinished++;
      if (threadsFinished==threadParameters->numberOfThreads) {
//         pthread_cond_broadcast(&tasksFinished);
          cout<<"This is another cout"<<endl;
          threadsFinished = 0;
          pthread_mutex_unlock(&tasksLock);
          pthread_mutex_lock(&allThreadsReady);

      }
       pthread_mutex_unlock(&remainingMux);

       //---------------------------
   }
   // pthread_mutex_unlock(&condLock);
   printf("%d exiting.\n",threadParameters->threadno);
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
   //while(remainingThreads < this->numberOfThreads) {
//    cout<<"going to wait"<<endl;
//       pthread_cond_wait(&threadsReady, &allThreadsReady);
 //  }
    pthread_mutex_lock(&tasksLock);
    cout << "Before broadcast"<<endl;
   pthread_cond_broadcast( &cond );
   cout << "After broadcast"<<endl;
   pthread_mutex_unlock(&allThreadsReady);
}

pthread_t JobScheduler::getWorkers(int i){
   return workers[i];
} //waits all submitted tasks to finish

void JobScheduler::wait_all_tasks_finish()
{
    cout<<"in wait all"<<endl;
   pthread_mutex_lock(&tasksLock);
   //while(threadsFinished < this->numberOfThreads){
    // pthread_cond_wait(&tasksFinished, &tasksLock);
  // }
    cout << "watf locked taskslock" << endl;
   pthread_mutex_unlock(&tasksLock);

   for (int j = 0; j < this->numOfJobs; j++) {
       cout<< results[j] << endl;
   }
   delete[] results;
}

bool JobScheduler::printQueue(){
   return this->jobs->printQueue();
}