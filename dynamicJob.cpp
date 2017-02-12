#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "job.h"
#include "bfs.h"

dynamicJob::dynamicJob(int id, int start, int goal, n_index* outIndex, buffer* outgoing, n_index* inIndex, buffer* incoming, int version , updateIndex* update_index){
   this->ID = id;
   this->startNode = start;
   this->goalNode = goal;
   this->update_index = update_index;
   this->outIndex = outIndex;
   this->inIndex = inIndex;
   this->incoming = incoming;
   this->outgoing = outgoing;
   this->version = version;
}

dynamicJob::~dynamicJob() {
   cout<<"job: "<<this->ID<<" finished"<<endl;
}

int dynamicJob::getVersion() {
   return this->version;
}

OK_SUCCESS dynamicJob::setVersion(int ver) {
   this->version = ver;
}

//  int executeQuery(grail* holy, n_index* outIndex, buffer* outgoing, n_index* inIndex, buffer* incoming);
int dynamicJob::executeQuery() {
    int BFSresult;
   if( outIndex->getCCnum(startNode) != outIndex->getCCnum(goalNode) ){
      int hasUpdateConnection = update_index->findConnection( outIndex->getCCnum(startNode), outIndex->getCCnum(goalNode) );
      if( hasUpdateConnection == NOT_IN_UPDATE_INDEX )
      {
         cout<<"No path between "<<startNode<<" and "<<goalNode<<endl;
         BFSresult = INVALID;
      }
      else if(hasUpdateConnection == ALREADY_IN_UPDATE_INDEX)
      {
//                        BFSresult = BBFS(Index, Buffer, startNode, Index_inv, Buffer_inv, goalNode, BFS_FRINGE_SIZE);
        BFSresult = DBBFS(outIndex, outgoing, startNode, inIndex, incoming, goalNode, BFS_FRINGE_SIZE, this->version);

      }
      else
      {
         cout<<"Error in updateIndex->findConnection with startNode "<<startNode<<" goalNode "<<goalNode<<endl;
         return FAIL;
      }
      update_index->setMetricValue(update_index->getMetricValue()+1);
   }
   else{
       BFSresult = DBBFS(outIndex, outgoing, startNode, inIndex, incoming, goalNode, BFS_FRINGE_SIZE, this->version);
//                     BFSresult = BBFS(Index, Buffer, startNode, Index_inv, Buffer_inv, goalNode, BFS_FRINGE_SIZE);
   }

return BFSresult;

}