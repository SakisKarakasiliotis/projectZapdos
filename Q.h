#ifndef Q_H
#define Q_H

#include "defines.h"

class queue
{
   private:
      uint32_t* q;
      int front, rear;
      int occupiedSpaces;
      int size;

      uint32_t next(uint32_t);
      void resizeBuffer();
   
   public:
      queue(int);
      ~queue();

      bool isFull();
      bool isEmpty();

      int getNumberOfElements();
      bool contains(uint32_t);

      bool enqueue(uint32_t);
      uint32_t dequeue(OK_SUCCESS);
};

#endif
