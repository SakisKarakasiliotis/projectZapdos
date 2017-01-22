#include <iostream>
#include <cstdio>

#include "jobQueue.h"
#include "job.h"

using namespace std;

jobQueue::jobQueue(int size)
{
   this->occupiedSpaces = 0;
   this->size = size;
   this->q = (job**) malloc(size * sizeof(job*));
   for(int i=0;i<size;i++){
    this->q[i]=NULL;
   }
   this->front=0;
   this->rear = this->size - 1;
}

bool jobQueue::isFull()
{
   if (this->occupiedSpaces == this->size)
      return true;
   return false;
}

bool jobQueue::isEmpty()
{
   if (this->occupiedSpaces == 0)
      return true;
   return false;
}

int jobQueue::getNumberOfElements()
{
   return this->occupiedSpaces;
}

int jobQueue::next(int position)
{
   if (position == this->size - 1)
      return 0;
   else
      return position + 1;
}

bool jobQueue::enqueue(job *x)
{
   if(this->isFull())
      this->resizeBuffer();
   rear = next(rear);
   q[rear]=x;
   this->occupiedSpaces++;
   printf("enqueue [%d %d->%d ?] in position %d\n", q[rear]->getID(), q[rear]->getStartNode(), q[rear]->getGoalNode(), rear);
   return true;
}

job* jobQueue::dequeue()
{
   if(this->isEmpty())
   {
      cout<<"\nQueue underflow!!\n";
      //error = FAIL;
      return NULL;
   }
   job* x = q[front];
   front = next(front);
   this->occupiedSpaces--;
   return x;
}

bool jobQueue::contains(job &target)
{
   // if (this->isEmpty())
   //    return false;
   // job tmp = front;
   // for (int i=0; i<occupiedSpaces; i++)
   // {
     
   //    if (this->q[tmp] == target) return true;
   //    tmp = next(tmp);
   // }
   // return false;
}

void jobQueue::resizeBuffer()
{
    int tmp = this->size;
   this->size *= 2;
   q = (job**) realloc(q, this->size*sizeof(job*));
    if (this->front == 0) return;
    for (int i=0; i<this->front; i++)
    {
        q[tmp] = q[i];
        tmp++;
    }
    this->rear = tmp-1;
}

bool jobQueue::printQueue() {
  if (this->isEmpty()) return false;
  printf("Printing queue:\n");
  printf("front = %d\n", this->front);
  printf("rear = %d\n", this->rear);
  for (int i = 0; i < size; i++){
    if(q[i]==NULL){
      cout<<"NULL"<<endl;
    }
    else printf("%d %d->%d ?\n", q[i]->getID(), q[i]->getStartNode(), q[i]->getGoalNode());
  }
  return true;
}

jobQueue::~jobQueue()
{
  free(this->q);
}
