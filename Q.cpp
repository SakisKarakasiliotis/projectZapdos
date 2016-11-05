#include <conio.h>
#include <iostream>

#include "Q.h"

using namespace std

queue::queue(uint32_t size)
{
   this->full = false;
   this->size = size;
   this->q = malloc(size * sizeof(uint32_t));
   this->front=0;
   this->rear=0;
}

bool isFull()
{
   return this->full;
}

bool isEmpty()
{
   return this->empty;
}

uint32_t queue::checkFrontValue(OK_SUCCESS* error)
{
   if (this->isEmpty)
      *error = FAIL;
   return this->q[front];
}

uint32_t queue::next(uint32_t position)
{
   if (position = this->size - 1)
      return 0;
   else
      return position + 1;
}

bool queue::enqueue(uint32_t x)
{
   if(this->isFull())
   {
      cout<<"\nQueue overflow!!\n";
      return false;
   }
   rear = next(rear);
   q[rear]=x;
   if (next(rear) == front)
      this->full = true;
   this->empty = false;
   this->occupiedSpaces++;
   return true;
}

uint32_t queue::dequeue(OK_SUCCESS* error)
{
   if(this->isEmpty)
   {
      cout<<"\nQueue underflow!!\n";
      *error = FAIL;
      return FAIL;
   }
   uint32_t x = q[front];
   if (rear == front)
      this->empty = true;
   else
      front = next(front);
   this->full = false;
   *error = OK;
   this->occupiedSpaces--;
   return x;
}

uint32_t* queue::toArray()
{
   if (this->isEmpty())
      return NULL;
   uint32_t* arr = malloc(occupiedSpaces*sizeof(uint32_t));
   uint32_t tmp = this->q[front];
   for (int i=0; i<occupiedSpaces; i++)
   {
      arr[i] = tmp;
      tmp = next(tmp);
   }
   return arr;
}

queue::~queue()
{
  free(this->q);
}
