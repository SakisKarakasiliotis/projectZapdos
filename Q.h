#ifndef Q_H
#define Q_H

class queue
{
private:
   bool empty, full;
   uint32_t* q;
   int front, rear;
   int size; 

public:
   queue(uint32_t);
   ~queue();

   bool isFull();
   bool isEmpty();
   uint32_t next(uint32_t);
   bool enqueue(uint32_t);
   int dequeue();
};

#endif