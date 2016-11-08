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
   queue* outChecked = new queue(outIndex->getNumberOfEntries());
   queue* inChecked = new queue(inIndex->getNumberOfEntries());

   int pathLength = 1;
   //--------------TEST CODE--------------
   //srand(time(NULL));
   //--------------TEST CODE--------------

   outFringe->enqueue(start);
   inFringe->enqueue(dest);
   outChecked->enqueue(start);
   inChecked->enqueue(dest);

   int numberOfNeighbors;
   uint32_t* neighbors;
   int iterations;
   uint32_t node;
   OK_SUCCESS error;
   n_index* workingIndex;
   queue *fringe, *otherFringe;
   buffer* graph;
   queue* checked;

   while (!outFringe->isEmpty() && !inFringe->isEmpty())
   {
      //*error = OK;
      error = OK;
      if (inFringe->getNumberOfElements() > outFringe->getNumberOfElements())
      {
         workingIndex = outIndex;
         graph = outgoing;
         fringe = outFringe;
         checked = outChecked;
         otherFringe = inFringe;
      }
      else
      {
         workingIndex = inIndex;
         graph = incoming;
         fringe = inFringe;
         checked = inChecked;
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
               delete inChecked;
               delete outChecked;
               delete inFringe;
               delete outFringe;
               return pathLength;
            }
            else if (!checked->contains(neighbors[i]))
            {
               fringe->enqueue(neighbors[i]);
               checked->enqueue(neighbors[i]);
            }
         }
      }
      pathLength++;
   }
   delete inChecked;
   delete outChecked;
   delete inFringe;
   delete outFringe;
   return INVALID;
}
