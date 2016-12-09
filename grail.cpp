//
// Created by Windows 8 on 09-Dec-16.
//

#include "grail.h"

grail::grail() {}

grail::grail(int sizeOfGrail) : sizeOfGrail(sizeOfGrail) {
    this->index = new n_index(sizeOfGrail);
    this->g_buffer = new buffer(sizeOfGrail,LIST_NODE_SIZE);
    ranks =(int**) malloc(UPDATE_INDEX_SIZE*sizeof(int*));
    for (int i = 0; i <UPDATE_INDEX_SIZE ; ++i) {
        ranks[i] = new int[2];
        ranks[i][MIN_RANK]=INVALID;
        ranks[i][RANK]=INVALID;
    }
}

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
