#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "job.h"
#include "bfs.h"

dynamicJob::dynamicJob(int id, int start, int goal, n_index* outIndex, buffer* outgoing, n_index* inIndex, buffer* incoming, int version) {
   this->ID = id;
   this->startNode = start;
   this->goalNode = goal;
   this->goblet = goblet;
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
   int BFSresult = 0;
   BFSresult = BBFS(outIndex, outgoing, start, inIndex, incoming, dest, BFS_FRINGE_SIZE, version);
   if (BFSresult == INVALID) {
      cout<<"There is no path from node "<<startNode<<" to "<<goalNode<<endl;
   } else {
      cout<<"Path length is: "<<BFSresult<<endl;
   }
   
   return BFSresult;
}