#include <iostream>
#include <cstdlib>

#include "Q.h"
#include "bfs.h"

using namespace std;

int BFS( nodeIndex* outIndex, buffer* outgoing, uint32_t start,
         nodeIndex* inIndex, buffer* incoming, uint32_t dest,
         int fringeSize )
{
   if (start == dest) return 0;

   queue* outFringe = malloc(fringeSize);
   queue* inFringe = malloc(fringeSize);
   int pathLength = 1;

   outFringe->enqueue(start);
   inFringe->enqueue(dest);

   int* numberOfNeighbors;
   int iterations;
   uint32_t node;
   OK_SUCCESS* error;
   queue *fringe, *otherFringe;
   buffer* graph;

   while (!outFringe.isEmpty() && !inFringe.isEmpty())
   {
      *error = OK;
      if (inFringe->getNumberOfElements() > outFringe->getNumberOfElements())
      {
         graph = outgoing;
         fringe = outFringe;
         otherFringe = inFringe;
      }
      else
      {
         graph = incoming;
         fringe = inFringe;
         otherFringe = outFringe;
      }
      iterations = fringe->getNumberOfElements()
      for (int j=0; j<iterations; j++)
      {
         node = fringe->dequeue(error);
         //TODO this is wrong based on the prototype plz fix, also pass the offset not the ID
         uint32_t* neighbors = graph->getNeighbors(node, numberOfNeighbors);
         for (int i=0; i<numberOfNeighbors; i++)
         {
            if (otherfringe->contains(neighbors[i]))
               return pathLength;
            else if (!fringe->contains(neighbors[i]))
               fringe->enqueue(neighbors[i]);
         }
      }
      pathLength++;
   }
   return INVALID;
}
