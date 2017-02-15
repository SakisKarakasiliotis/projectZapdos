#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Q.h"
#include "bfs.h"

using namespace std;

int BBFS(n_index* outIndex, buffer* outgoing, uint32_t start, n_index* inIndex, buffer* incoming, uint32_t dest, int fringeSize)
{
   if (start == dest) return 0;

   queue* outFringe = new queue(fringeSize);
   queue* inFringe = new queue(fringeSize);
   queue* outChecked = new queue(outIndex->getNumberOfEntries());
   queue* inChecked = new queue(inIndex->getNumberOfEntries());

   int pathLength = 1;


   outFringe->enqueue(start);
   inFringe->enqueue(dest);
   outChecked->enqueue(start);
   inChecked->enqueue(dest);

   int numberOfNeighbors;
   uint32_t* neighbors;
   int iterations;
   int node;
   OK_SUCCESS error;
   n_index* workingIndex;
   queue *fringe, *otherFringe;
   buffer* graph;
   queue* checked;

   while (!outFringe->isEmpty() && !inFringe->isEmpty())
   {
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
          if (node == INVALID) continue;
          neighbors = graph->getNeighbors(numberOfNeighbors, node);

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

int DBBFS(n_index* outIndex, buffer* outgoing, uint32_t start, n_index* inIndex, buffer* incoming, uint32_t dest, int fringeSize, int version)
{
   if (start == dest) return 0;

   queue* outFringe = new queue(fringeSize);
   queue* inFringe = new queue(fringeSize);
   queue* outChecked = new queue(outIndex->getNumberOfEntries());
   queue* inChecked = new queue(inIndex->getNumberOfEntries());

   int pathLength = 1;

   outFringe->enqueue(start);
   inFringe->enqueue(dest);
   outChecked->enqueue(start);
   inChecked->enqueue(dest);

   int numberOfNeighbors;
   uint32_t* neighbors;
   int iterations;
   int node;
   OK_SUCCESS error;
   n_index* workingIndex;
   queue *fringe, *otherFringe;
   buffer* graph;
   queue* checked;

   while (!outFringe->isEmpty() && !inFringe->isEmpty())
   {
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
          if (node == INVALID) continue;
          neighbors = graph->getNeighbors(numberOfNeighbors, node, version);

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

OK_SUCCESS GetConnectedComponents(n_index* outIndex, buffer* outgoing, n_index* inIndex, buffer* incoming)
{
    bool key = true;
    bool updateCCNum = false;
    uint32_t startNode;
    int ccnum = 0;
    queue* fringe = new queue(outIndex->getSizeOfIndex());
    uint32_t* inNeighbors;
    uint32_t* outNeighbors;
    int numberOfNeighbors = 0;
    int CCgroup = 0;
    OK_SUCCESS error;
    int iterNo = 0;

    srand (time(NULL));
    do{
        startNode = rand() % outIndex->getSizeOfIndex();
        if(outIndex->getEntry(startNode) != INVALID || inIndex->getEntry(startNode) != INVALID ) key = false;
    }while( key );
    fringe->enqueue(startNode);

    while (iterNo < outIndex->getNumberOfEntries())
    {
        while (!fringe->isEmpty())
        {
            int nodeName = fringe->dequeue(error);
            if((ccnum = outIndex->getCCnum(nodeName)) == FAIL ){
                return FAIL;
            }else if(ccnum != INVALID){
                continue;
            }
            else if(ccnum == INVALID){
                outIndex->setCCnum(nodeName, CCgroup);
                inIndex->setCCnum(nodeName, CCgroup);
                int outNodeOffset = outIndex->getEntry(nodeName);
                if(outNodeOffset != INVALID){
                    outNeighbors = outgoing->getNeighbors(numberOfNeighbors, outNodeOffset);//TODO:: reinitialize outNeighhor!!!!!!!!!!!
                    if(outNeighbors != NULL){
                        updateCCNum = true;
                        for (int i=0; i<numberOfNeighbors; i++)
                        {
                            fringe->enqueue(outNeighbors[i]);
                        }
                        numberOfNeighbors=0;
                    }
                }
                int inNodeOffset = inIndex->getEntry(nodeName);
                if(inNodeOffset!=INVALID) {
                    inNeighbors = incoming->getNeighbors(numberOfNeighbors, inNodeOffset);
                   if(inNeighbors == NULL){
                        cout<<"not OK"<<endl;
                    }else{
                        updateCCNum = true;
                        for (int i = 0; i < numberOfNeighbors; i++) {
                            fringe->enqueue(inNeighbors[i]);
                        }
                        numberOfNeighbors = 0;
                    }
                }
            }
        }

        if(updateCCNum){
            CCgroup++;
            updateCCNum = false;
        }

        while(iterNo<outIndex->getNumberOfEntries()){

            if (outIndex->getCCnum(iterNo) == INVALID)
            {
                startNode = iterNo;
                fringe->enqueue(startNode);
                iterNo++;
                break;
            }
            iterNo++;
        }


    }
    outIndex->setTotalConnectedComponents(CCgroup);
    inIndex->setTotalConnectedComponents(CCgroup);
    delete fringe;
    return OK;
}