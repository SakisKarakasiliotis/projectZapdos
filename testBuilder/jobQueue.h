#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include "defines.h"
#include "job.h"

class jobQueue
{
   private:
      job** q;
      int front, rear;
      int occupiedSpaces;
      int size;

      int next(int);
      void resizeBuffer();
   
   public:
      jobQueue(int);
      ~jobQueue();

      bool isFull();
      bool isEmpty();

      int getNumberOfElements();
      bool contains(job&);

      bool enqueue(job*);
      job* dequeue();
};

#endif