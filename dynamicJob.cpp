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
}

int dynamicJob::getVersion() {
   return this->version;
}

OK_SUCCESS dynamicJob::setVersion(int ver) {
   this->version = ver;
}

int dynamicJob::executeQuery() {
    int BFSresult;
   if( outIndex->getCCnum(startNode) != outIndex->getCCnum(goalNode) ){
      int hasUpdateConnection = update_index->findConnection( outIndex->getCCnum(startNode), outIndex->getCCnum(goalNode) , this->version);
      if( hasUpdateConnection == NOT_IN_UPDATE_INDEX )
      {
         BFSresult = INVALID;
      }
      else if(hasUpdateConnection == ALREADY_IN_UPDATE_INDEX)
      {
        BFSresult = DBBFS(outIndex, outgoing, startNode, inIndex, incoming, goalNode, BFS_FRINGE_SIZE, this->version);
      }
      else
      {
         return FAIL;
      }
      update_index->setMetricValue(update_index->getMetricValue()+1);
   }
   else{
       BFSresult = DBBFS(outIndex, outgoing, startNode, inIndex, incoming, goalNode, BFS_FRINGE_SIZE, this->version);
   }

return BFSresult;

}