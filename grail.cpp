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

int **grail::getRanks() const {
    return ranks;
}

void grail::setRanks(int **ranks) {
    grail::ranks = ranks;
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

// TODO ADD TARJAN
OK_SUCCESS grail::calculateSCC(n_index *subGraphIndex, buffer *subGraphBuffer) {
    return 0;
}

OK_SUCCESS grail::initializeGrail() {
    if( (this->sizeOfGrail = this->SCC->getComponentsCount()) <= 0 ){
        this->sizeOfGrail = INVALID;
        cout<<"getComponentsCount failed in initializeGrail"<<endl;
        return FAIL;
    }
    this->index = new n_index(this->sizeOfGrail);
    this->g_buffer = new buffer(this->sizeOfGrail,LIST_NODE_SIZE);
    ranks =(int**) malloc(this->sizeOfGrail*sizeof(int*));
    for (int i = 0; i <this->sizeOfGrail ; i++) {
        ranks[i] = new int[2];
        ranks[i][MIN_RANK]=INVALID;
        ranks[i][RANK]=INVALID;
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
    stack* Stack = new stack(this->sizeOfGrail);
    int startNode;
    int rank=1;
    bool key = true;
    srand (time(NULL));
    int restart = 0;

    do{
        startNode = rand() % index->getSizeOfIndex();
        if(index->getEntry(startNode) != INVALID) key = false;
    }while( key );
    Stack->push(startNode);

    do{
        int nodeOffset = index->getEntry(startNode);
        int numberOfNeighbors;
        uint32_t * neighbors;
        if(nodeOffset == INVALID){
            neighbors = NULL;
        }
        else{
            neighbors = g_buffer->getNeighbors(numberOfNeighbors, nodeOffset);
        }

         if (neighbors != NULL){
             int minrank=rank;
             int i;
             for ( i = 0; i < numberOfNeighbors ; i++) {
                 if(this->ranks[neighbors[i]][MIN_RANK] < minrank && this->ranks[neighbors[i]][MIN_RANK] >0){
                     minrank = this->ranks[neighbors[i]][MIN_RANK];
                 }
                 if(this->ranks[neighbors[i]][MIN_RANK] != INVALID &&  this->ranks[neighbors[i]][RANK] != INVALID){
                     continue;
                 }
                 else{
                     Stack->push(neighbors[i]);
                     startNode = neighbors[i];
                     break;
                 }
             }
             if(i == numberOfNeighbors) {
                 this->ranks[startNode][RANK] = rank;
                 this->ranks[startNode][MIN_RANK] = minrank;
                 rank++;
                 startNode = Stack->pop();
             }
         }
         else{
             this->ranks[startNode][RANK] = rank;
             this->ranks[startNode][MIN_RANK] = rank;
             startNode = Stack->pop();
             rank++;
         }
        if(startNode == INVALID ){
            while (restart < this->sizeOfGrail ){
                if(this->ranks[restart][RANK] == INVALID){
                    startNode = restart;
                    Stack->push(startNode);
                    break;
                }
                restart++;
            }
        }
    }while(!Stack->isEmpty());

    return OK;
}

OK_SUCCESS grail::askGrail(int from, int to) {
    if(from<0 || to<0 || from>this->sizeOfGrail || to>this->sizeOfGrail){
        cout<<"Out of bounds on askGrail with from "<<from<<" to "<<to<<endl;
        return FAIL;
    }
    if(this->SCC->checkBelongsToComponent(from) == this->SCC->checkBelongsToComponent(to)){
        return YES;
    }
    int from_min_rank = this->ranks[from][MIN_RANK];
    int from_rank = this->ranks[from][RANK];
    int to_min_rank = this->ranks[to][MIN_RANK];
    int to_rank = this->ranks[to][RANK];

    if( to_min_rank >= from_min_rank && to_rank <= from_rank ) return MAYBE;
    return NO;
}
