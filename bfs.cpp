#include <iostream>
#include <cstdlib>

#include "Q.h"
#include "bfs.h"

using namespace std;


int BFS(n_index* outIndex, buffer* outgoing, uint32_t start, n_index* inIndex, buffer* incoming, uint32_t dest, int fringeSize)
{
   if (start == dest) return 0;

   queue* outFringe = new queue(fringeSize);
   queue* inFringe = new queue(fringeSize);

   int pathLength = 1;
   //--------------TEST CODE--------------
   //srand(time(NULL));
   //--------------TEST CODE--------------

   outFringe->enqueue(start);
   inFringe->enqueue(dest);

   int numberOfNeighbors;
   uint32_t* neighbors;
   int iterations;
   uint32_t node;
   OK_SUCCESS* error;
   n_index* workingIndex;
   queue *fringe, *otherFringe;
   buffer* graph;

   while (!outFringe->isEmpty() && !inFringe->isEmpty())
   {
      *error = OK;
      if (inFringe->getNumberOfElements() > outFringe->getNumberOfElements())
      {
         workingIndex = inIndex;
         graph = outgoing;
         fringe = outFringe;
         otherFringe = inFringe;
      }
      else
      {
         workingIndex = outIndex;
         graph = incoming;
         fringe = inFringe;
         otherFringe = outFringe;
      }
      iterations = fringe->getNumberOfElements();
      for (int j=0; j<iterations; j++)
      {
         node = workingIndex->getEntry(fringe->dequeue(error));
         numberOfNeighbors = graph->getNeighbors(neighbors, node);
         //--------------TEST CODE--------------
         // node = 8;
         // numberOfNeighbors = 10;
         // neighbors = (uint32_t*) malloc(numberOfNeighbors*sizeof(uint32_t));
         // for (int i=0; i<numberOfNeighbors; i++)
         //    neighbors[i] = rand()%100;
         //--------------TEST CODE--------------
         for (int i=0; i<numberOfNeighbors; i++)
         {
            if (otherFringe->contains(neighbors[i]))
            {
               delete inFringe;
               delete outFringe;
               return pathLength;
            }
            else if (!fringe->contains(neighbors[i]))
               fringe->enqueue(neighbors[i]);
         }
      }
      pathLength++;
   }
   delete inFringe;
   delete outFringe;
   return INVALID;
}
