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

uint32_t queue::next(uint32_t position)
{
   if (position = this->size - 1)
      return 0;
   else
      return position + 1;
}

void queue::enqueue(uint32_t x)
{
   if(this->isFull())
   {
      cout<<"\nQueue overflow!!\n";
      return;
   }
   q[rear]=x;
   rear = next(rear);
   if (rear == front)
      this->full = true;
   this->empty = false;
}

uint32_t queue::dequeue()
{
   if(this->isEmpty)
   {
      cout<<"\nQueue underflow!!\n";
      return;
   }
   uint32_t x = q[front];
   front = next(front);
   if (rear == front)
      this->empty = true;
   this->full = false;
   return x;
}

queue::~queue()
{
  free(this->q);
}