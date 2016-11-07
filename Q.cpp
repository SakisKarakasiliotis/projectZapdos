#include <iostream>

#include "Q.h"

using namespace std;

queue::queue(int size)
{
   this->occupiedSpaces = 0;
   this->size = size;
   this->q = (uint32_t*) malloc(size * sizeof(uint32_t));
   this->front=0;
   this->rear = this->size - 1;
}

bool queue::isFull()
{
   if (this->occupiedSpaces == this->size)
      return true;
   return false;
}

bool queue::isEmpty()
{
   if (this->occupiedSpaces == 0)
      return true;
   return false;
}

int queue::getNumberOfElements()
{
   return this->occupiedSpaces;
}

uint32_t queue::next(uint32_t position)
{
   if (position == this->size - 1)
      return 0;
   else
      return position + 1;
}

bool queue::enqueue(uint32_t x)
{
   if(this->isFull())
      this->resizeBuffer();
   rear = next(rear);
   q[rear]=x;
   this->occupiedSpaces++;
   return true;
}

uint32_t queue::dequeue(OK_SUCCESS* error)
{
   if(this->isEmpty())
   {
      cout<<"\nQueue underflow!!\n";
      *error = FAIL;
      return FAIL;
   }
   uint32_t x = q[front];
   front = next(front);
   *error = OK;
   this->occupiedSpaces--;
   return x;
}

bool queue::contains(uint32_t target)
{
   if (this->isEmpty())
      return false;
   uint32_t tmp = front;
   for (int i=0; i<occupiedSpaces; i++)
   {
      cout << "cointains: iteration No " << i << endl;
      cout << "front: " << this->front << endl;
      cout << "rear: " << this->rear << endl << endl;
      if (this->q[tmp] == target) return true;
      tmp = next(tmp);
   }
   return false;
}

void queue::resizeBuffer()
{
   this->size *= 2;
   q = (uint32_t*) realloc(q, this->size*sizeof(uint32_t));
}

queue::~queue()
{
  free(this->q);
}
