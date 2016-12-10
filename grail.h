//
// Created by Windows 8 on 09-Dec-16.
//

#ifndef PROJECTZAPDOS_GRAIL_H
#define PROJECTZAPDOS_GRAIL_H

#include <iostream>



#include "index.h"
#include "buffer.h"
#include "stronglyConnectedComponents.h"
#include "rank.h"

class grail {
private:
    n_index* index;
    rank *ranks;
    int sizeOfGrail; // number of SCC
    buffer* g_buffer;
    stronglyConnectedComponents* SCC;

public:
    grail();

    stronglyConnectedComponents *getSCC() const;

    void setSCC(stronglyConnectedComponents *SCC);

    buffer *getG_buffer() const;

    void setG_buffer(buffer *g_buffer);

    ~grail();

    n_index *getIndex() const;

    void setIndex(n_index *index);


    int getSizeOfGrail() const;

    void setSizeOfGrail(int sizeOfGrail);

    OK_SUCCESS calculateSCC(n_index* subGraphIndex, buffer* subGraphBuffer);

    OK_SUCCESS initializeGrail();

    OK_SUCCESS generateHyperGraph(n_index *subGraphIndex, buffer *subGraphBuffer);

    OK_SUCCESS calculateRanks();

    OK_SUCCESS askGrail(int from , int to);
};


#endif //PROJECTZAPDOS_GRAIL_H
