//
// Created by Windows 8 on 09-Dec-16.
//

#include <time.h>
#include "grail.h"
#include "stack.h"

grail::grail() {}

grail::~grail() {
    std::cout<<"the end is near"<<std::endl;
}

n_index *grail::getIndex() const {
    return index;
}

void grail::setIndex(n_index *index) {
    grail::index = index;
}

int grail::getSizeOfGrail() const {
    return sizeOfGrail;
}

void grail::setSizeOfGrail(int sizeOfGrail) {
    grail::sizeOfGrail = sizeOfGrail;
}

buffer *grail::getG_buffer() const {
    return g_buffer;
}

void grail::setG_buffer(buffer *g_buffer) {
    grail::g_buffer = g_buffer;
}

stronglyConnectedComponents *grail::getSCC() const {
    return SCC;
}

void grail::setSCC(stronglyConnectedComponents *SCC) {
    grail::SCC = SCC;
}

OK_SUCCESS grail::initializeGrail() {
    if( (this->sizeOfGrail = this->SCC->getComponentsCount()) <= 0 ){
        this->sizeOfGrail = INVALID;
        cout<<"getComponentsCount failed in initializeGrail"<<endl;
        return FAIL;
    }
    this->index = new n_index(this->sizeOfGrail);
    this->g_buffer = new buffer(this->sizeOfGrail,LIST_NODE_SIZE);
    this->ranks = (rank*) malloc(RANK_SIZE * sizeof(rank));
    for (int i = 0; i < RANK_SIZE; ++i) {
        ranks[i] = *new rank(this->sizeOfGrail);
    }
    return OK;
}

OK_SUCCESS grail::generateHyperGraph(n_index *subGraphIndex, buffer *subGraphBuffer) {
    cout<<"GENERATING HYPERGRAPH"<<endl;
    if(subGraphIndex == NULL || subGraphBuffer==NULL){
        cout<<"Parameters contain NULL values"<<endl;
        return FAIL;
    }
    for (int i = 0; i < this->sizeOfGrail; i++) {
        component* currentComponent = this->SCC->getComponent(i);
        if(currentComponent == NULL){
            cout<<"Requested component "<<i<<" is NULL on generateHyperGraph"<<endl;
            return FAIL;
        }
        for (int j = 0; j < currentComponent->getNumberOfNodes(); j++) {
            int currentNode = currentComponent->getNode(j);
            if(currentNode == FAIL || currentNode < 0){
                cout<<"Requested node "<<currentNode<<" Failed on generateHypergraph"<<endl;
                return FAIL;
            }
            int currentNodeOffset = subGraphIndex->getEntry(currentNode);
            if(currentNodeOffset == FAIL){
                cout<<"Requested offset "<<currentNodeOffset<<" Failed on generateHypergraph"<<endl;
                return FAIL;
            }
            if(currentNodeOffset == INVALID){
                cout<<"Node "<<currentNode<<" with offset "<<currentNodeOffset<<" requested has no neighbors on generateHypergraph"<<endl;
                continue;
            }
            int numberOfNeighbors;
            uint32_t * currentNodeNeighbors = subGraphBuffer->getNeighbors(numberOfNeighbors, currentNodeOffset);
            if( currentNodeNeighbors == NULL){
                cout<<"Couldn't manage to get neighbors of "<<currentNode<<" on generateHypergraph on getNeighbors with offset "<<currentNodeOffset<<endl;
                return FAIL;
            }
            for (int k = 0; k < numberOfNeighbors; k++) {
                int currentNeigbor = currentNodeNeighbors[k];
                int currentNeighborCompId = this->SCC->checkBelongsToComponent(currentNeigbor);
                if(currentNeighborCompId == FAIL){
                    cout<<"Requested neighbor "<<currentNeigbor<<" Failed on generateHypergraph on checkBelongsToComponent"<<endl;
                    return FAIL;
                }
                if(currentComponent->getCompId() != currentNeighborCompId){
                    if(index->getEntry(currentComponent->getCompId())==INVALID){
                        int temp = g_buffer->addListNode();
                        index->addEntry(temp,currentComponent->getCompId());
                    }
                    g_buffer->insertNeighbor(index->getEntry(currentComponent->getCompId()),currentNeighborCompId);
                }else{
                    continue;
                }

            }
        }
    }
    cout<<"HOUSTON WE HAVE A HYPERGRAPH"<<endl;
    return OK;
}

OK_SUCCESS grail::calculateRanks() {
   for(int rankiter = 0 ; rankiter <RANK_SIZE ; rankiter++){
      stack *Stack = new stack(this->sizeOfGrail);
      int startNode;
      int rank = 1;
      bool key = true;
      srand(time(NULL));
      int restart = 0;
       if(index->getSizeOfIndex() > 1){
           do {
               startNode = rand() % index->getSizeOfIndex();
               if (index->getEntry(startNode) != INVALID) key = false;
           } while (key);
       }else{
           startNode = 0;
       }

      Stack->push(startNode);

      do {
         int nodeOffset = index->getEntry(startNode);
         int numberOfNeighbors;
         uint32_t *neighbors;
         if (nodeOffset == INVALID) {
            neighbors = NULL;
         } else {
            neighbors = g_buffer->getNeighbors(numberOfNeighbors, nodeOffset);
         }

         if (neighbors != NULL) {
            int minrank = rank;
            int i;
            for (i = 0; i < numberOfNeighbors; i++) {
               if (this->ranks[rankiter].getMinRank(neighbors[i]) < minrank && this->ranks[rankiter].getMinRank(neighbors[i]) > 0) {
                  minrank = this->ranks[rankiter].getMinRank(neighbors[i]);
               }
               if (this->ranks[rankiter].getMinRank(neighbors[i]) != INVALID && this->ranks[rankiter].getRank(neighbors[i]) != INVALID) {
                  continue;
               } else {
                  Stack->push(neighbors[i]);
                  startNode = neighbors[i];
                  break;
               }
            }
            if (i == numberOfNeighbors) {
               this->ranks[rankiter].setRank(neighbors[i],rank);
               this->ranks[rankiter].setMinRank(neighbors[i],minrank);
               rank++;
               startNode = Stack->pop();
            }
         } else {
            this->ranks[rankiter].setRank(startNode,rank);
            this->ranks[rankiter].setMinRank(startNode,rank);
            startNode = Stack->pop();
            rank++;
         }
         if (startNode == INVALID) {
            while (restart < this->sizeOfGrail) {
               if (this->ranks[rankiter].getRank(restart) == INVALID) {
                  startNode = restart;
                  Stack->push(startNode);
                  break;
               }
               restart++;
            }
         }
          cout<<"Trying 2 bro"<<endl;
      } while (!Stack->isEmpty());
   }
    return OK;
}

OK_SUCCESS grail::askGrail(int from, int to) {
    if(from<0 || to<0 ){
        cout<<"Out of bounds on askGrail with from "<<from<<" to "<<to<<endl;
        return FAIL;
    }
    if(this->SCC->checkBelongsToComponent(from) == this->SCC->checkBelongsToComponent(to)){
        return YES;
    }
   for(int i=0; i<RANK_SIZE;i++){
      if(this->ranks[i].askRank(from,to)== NO){
         return NO;
      }
   }
    return MAYBE;
}

int grail::getSCCId(int nodeName) {
   if (nodeName < 0) return FAIL;
   return this->SCC->checkBelongsToComponent(nodeName);
}
