//
// Created by Marcus on 11/12/2016.
//
#include <iostream>
#include <cstdlib>

#include "StaticBFS.h"
#include "Q.h"

int SBBFS(grail* goblet, n_index* outIndex, buffer* outgoing, uint32_t start, n_index* inIndex, buffer* incoming, uint32_t dest, int fringeSize) {
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
   uint32_t nodeName;
   int iterations;
   int node;
   OK_SUCCESS error;
   n_index* workingIndex;
   queue *fringe, *otherFringe;
   buffer* graph;
   queue* checked;
   bool checkingReverse = false;
   
   while (!outFringe->isEmpty() && !inFringe->isEmpty())
   {
      //*error = OK;
      error = OK;
      if (inFringe->getNumberOfElements() > outFringe->getNumberOfElements())
      {
         checkingReverse = false;
         workingIndex = outIndex;
         graph = outgoing;
         fringe = outFringe;
         checked = outChecked;
         otherFringe = inFringe;
      }
      else
      {
         checkingReverse = true;
         workingIndex = inIndex;
         graph = incoming;
         fringe = inFringe;
         checked = inChecked;
         otherFringe = outFringe;
      }
      iterations = fringe->getNumberOfElements();
      for (int j=0; j<iterations; j++)
      {
         nodeName = fringe->dequeue(error);
         node = workingIndex->getEntry(nodeName);
         if (node == INVALID) continue;
         neighbors = graph->getNeighbors(numberOfNeighbors, node);
         //--------------TEST CODE--------------
         // node = 8;
         // numberOfNeighbors = 10;
         // neighbors = (uint32_t*) malloc(numberOfNeighbors*sizeof(uint32_t));
         // for (int i=0; i<numberOfNeighbors; i++)
         //    neighbors[i] = rand()%100;
         //--------------TEST CODE--------------
         for (int i=0; i<numberOfNeighbors; i++)
         {
            //check if there is a path
            if (goblet->getSCCId(neighbors[i]) != goblet->getSCCId(nodeName)) {
               if (checkingReverse) {
                   if (goblet->askGrail(start, nodeName) == NO) continue;
               }
               if (goblet->askGrail(nodeName, dest) == NO) continue;
            }
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

