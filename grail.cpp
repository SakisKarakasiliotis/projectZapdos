//
// Created by Windows 8 on 09-Dec-16.
//

#include "grail.h"

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
