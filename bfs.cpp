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
             cout<<"in dbfs "<<neighbors[i]<<endl;
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
//24921 important for small
OK_SUCCESS GetConnectedComponents(n_index* outIndex, buffer* outgoing, n_index* inIndex, buffer* incoming)
{
    cout<<"INIT GCC"<<endl;
    srand (time(NULL));
    bool key = true;
    uint32_t startNode;
    do{
        startNode = rand() % outIndex->getSizeOfIndex();
        if(outIndex->getEntry(startNode) != INVALID || inIndex->getEntry(startNode) != INVALID ) key = false;
    }while( key );

    cout<<"First node: "<<startNode<<endl;
    int ccnum = 0;
    queue* fringe = new queue(outIndex->getSizeOfIndex());
    fringe->enqueue(startNode);
    uint32_t* inNeighbors;
    uint32_t* outNeighbors;
    int numberOfNeighbors = 0;
    int CCgroup = 0;
    OK_SUCCESS error;
    int iterNo = 0;
    cout<<"First GO at GCC"<<endl;
    while (iterNo < outIndex->getSizeOfIndex())
    {
       // cout<<"Before inner While: "<<iterNo<<endl;
        while (!fringe->isEmpty())
        {
            int nodeName = fringe->dequeue(error);
           // cout<<"nodename: "<<nodeName<<endl;
            if((ccnum = outIndex->getCCnum(nodeName)) == FAIL ){
                cout<<nodeName<<" Out of bounds on GetVonnectedComponents"<<endl;
                return FAIL;
            }else if(ccnum != INVALID){
                //cout<<"got not invalid ccnum"<<endl;
                continue;
            }
            else if(ccnum == INVALID){
                outIndex->setCCnum(nodeName, CCgroup);
                inIndex->setCCnum(nodeName, CCgroup);
                int outNodeOffset = outIndex->getEntry(nodeName);
                if(outNodeOffset != INVALID){
                    outNeighbors = outgoing->getNeighbors(numberOfNeighbors, outNodeOffset);
                    //cout<<"This should print NON "<<numberOfNeighbors<<endl;
                    if(outNeighbors == NULL){
                        cout<<"OK"<<endl;
                        continue;
                    }
                    for (int i=0; i<numberOfNeighbors; i++)
                    {
                       // cout<<"adding in queue from outN"<<numberOfNeighbors<<endl;
//                        cout<<"adding in queue from outN "<<(int) outNeighbors[i]<<endl;
                        fringe->enqueue(outNeighbors[i]);
                    }
                    numberOfNeighbors=0;
                }
                int inNodeOffset = inIndex->getEntry(nodeName);
                if(inNodeOffset!=INVALID) {
                    inNeighbors = incoming->getNeighbors(numberOfNeighbors, inNodeOffset);
                    for (int i = 0; i < numberOfNeighbors; i++) {
                      //   cout<<"adding in queue from inN"<<numberOfNeighbors<<endl;
                       //  cout<<"adding in queue from inN"<<" "<<inNeighbors[i]<<endl;

                        fringe->enqueue(inNeighbors[i]);
                    }
                    numberOfNeighbors = 0;
                }
            }
        }
//        cout<<CCgroup <<"this is the CCno"<<endl;
        CCgroup++;
//        cout<<CCgroup<<"this should be +1"<<endl;
        while(iterNo<outIndex->getSizeOfIndex()){
            //cout<<"inside for stat"<<iterNo<<endl;
            int nodeOffset = outIndex->getEntry(iterNo);
            if (outIndex->getCCnum(nodeOffset) == INVALID)
            {
                startNode = iterNo;
                fringe->enqueue(startNode);
                //cout<<iterNo<<"if inside for"<<endl;
                iterNo++;
                break;
            }
            iterNo++;
        }


    }
    cout<<"curent CC grp:"<<CCgroup<<endl;
    delete fringe;
    return OK;
}