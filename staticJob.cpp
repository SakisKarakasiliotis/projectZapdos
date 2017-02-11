#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "job.h"
#include "staticBFS.h"

staticJob :: staticJob(int id, int start, int goal, grail* goblet, n_index* outIndex, buffer* outgoing, n_index* inIndex, buffer* incoming){
   this->ID = id;
   this->startNode = start;
   this->goalNode = goal;
   this->goblet = goblet;
   this->outIndex = outIndex;
   this->inIndex = inIndex;
   this->incoming = incoming;
   this->outgoing = outgoing;
}

staticJob :: ~staticJob(){
   cout<<"job: "<<this->ID<<" finished"<<endl;
}

int staticJob :: executeQuery(){
   int BFSresult = 0;
   int grailResponse = goblet->askGrail(startNode, goalNode);
   if (grailResponse == YES || grailResponse == MAYBE) {
      BFSresult = SBBFS(goblet, outIndex, outgoing, startNode, inIndex, incoming, goalNode, BFS_FRINGE_SIZE);
      if (BFSresult == INVALID) {
         cout<<"There is no path from node "<<startNode<<" to "<<goalNode<<endl;
      } else {
         cout<<"Path length is: "<<BFSresult<<endl;
      }
   }
   else {
      BFSresult = INVALID;
      cout<<"There is no path from node "<<startNode<<" to "<<goalNode<<endl;
   }
   return BFSresult;
}