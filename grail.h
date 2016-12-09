//
// Created by Windows 8 on 09-Dec-16.
//

#ifndef PROJECTZAPDOS_GRAIL_H
#define PROJECTZAPDOS_GRAIL_H

#include <iostream>



#include "index.h"
#include "buffer.h"

class grail {
private:
    n_index* index;
    int **ranks;
    int sizeOfGrail; // number of SCC
    buffer* g_buffer;

public:
    grail();

    grail(int sizeOfGrail);

    buffer *getG_buffer() const;

    void setG_buffer(buffer *g_buffer);

    ~grail();

    n_index *getIndex() const;

    void setIndex(n_index *index);

    int **getRanks() const;

    void setRanks(int **ranks);

    int getSizeOfGrail() const;

    void setSizeOfGrail(int sizeOfGrail);

};


#endif //PROJECTZAPDOS_GRAIL_H
