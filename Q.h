#ifndef Q_H
#define Q_H

class queue
{
private:
   bool empty, full;
   uint32_t* q;
   int front, rear;
   int size;

   uint32_t next(uint32_t);

public:
   queue(uint32_t);
   ~queue();

   bool isFull();
   bool isEmpty();

   uint32_t checkFrontValue(OK_SUCCESS*);
   bool enqueue(uint32_t);
   int dequeue(OK_SUCCESS*);
};

#endif
